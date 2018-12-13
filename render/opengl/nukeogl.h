#ifndef NUKEOGL_H
#define NUKEOGL_H
#include "../irender.h"
#include <input/keyboard.h>
#include <input/mouse.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <boost/thread.hpp>
#include <iostream>

using namespace std;
namespace bc = boost::container;

void oglkeyboard(unsigned char c, int x, int y);
void oglspecialkeyboard(int key, int x, int y);
void oglkeyboardup(unsigned char c, int x, int y);
void oglspecialkeyboardup(int key, int x, int y);
void oglmouse (int button, int state, int x, int y);
void oglmousescroll(int button, int dir, int x, int y);
void oglreshape(int width, int height);
void oglidle(void);
void ogldisplay(void);
void oglclose();
void oglmove(int x, int y);
void oglpmove(int x, int y);
void ogltimer(int t);

class NukeOGL : public iRender
{
private:
    bc::list<b::function<void()>> _onClose;
    b::function<void()> _physTrigger;
    bc::list<b::function<void(void)>> _onRender;
    bc::list<b::function<void(void)>> _onGUI;

    static NukeOGL* _main;

    GLuint fbo; // The frame buffer object
    GLuint fbo_depth; // The depth buffer for the frame buffer object
    GLuint fbo_texture; // The texture object to write our frame buffer object to

public:
    NukeOGL(){
        if(_main)
            _instance = _main;
        else
        {
            _main = this;
            _instance = _main;
        }
    }
    ~NukeOGL(){}
    b::function<void()> _UIinit;
    b::function<void(unsigned char c, int x, int y)> _UIkeyboard;
    b::function<void(unsigned char c, int x, int y)> _UIkeyaboardUp;
    b::function<void(int key, int x, int y)> _UIspecial;
    b::function<void(int key, int x, int y)> _UIspecialUp;
    b::function<void(int button, int state, int x, int y)> _UImouse;
    b::function<void(int button, int dir, int x, int y)> _UImouseWheel;
    b::function<void(int x, int y)> _UImove;
    b::function<void(int x, int y)> _UIpmove;
    b::function<void(int w, int h)> _UIreshape;

    static NukeOGL* getSingleton()
    {
        //static NukeOGL instance;
        if(!_main)
            _main = new NukeOGL();
        return _main;
    }

    unsigned int getRenderTexture(){
        return fbo_texture;
    }

    void setOnClose(b::function<void()> cb){
        _onClose.push_back(cb);
    }

    void setOnGUI(b::function<void(void)> cb){
        _onGUI.push_back(cb);
//        cout << cb << " -- onGUI[" << this << "]" << endl;
    }

    void setOnRender(b::function<void(void)> cb){
        _onRender.push_back(cb);
//        cout << cb << " -- onRender" << endl;
    }

    void close()
    {
        if(_onClose.size() > 0)
            for(auto cb : _onClose)
                cb();
    }

    void move(int x, int y)
    {
        //cout << "mov [ " << x << ", " << y << " ]" << endl;
        Mouse::getSingleton()->move(x,y);
        if(_UImove)
            _UImove(x,y);
    }

    void passmove(int x, int y)
    {
        //cout << "pmov [ " << x << ", " << y << " ]" << endl;
        Mouse::getSingleton()->pmove(x,y);
        if(_UImove)
            _UImove(x,y);
    }

    void keyboard(unsigned char c, int x, int y) {
        KeyBoard::getSingleton()->key(c,x,y);
        if(_UIkeyboard)
            _UIkeyboard(c,x,y);
    }
    void keyboardUp(unsigned char c, int x, int y) {
        KeyBoard::getSingleton()->keyup(c,x,y);
        if(_UIkeyaboardUp)
            _UIkeyaboardUp(c,x,y);
    }
    void special(int key, int x, int y){
        KeyBoard::getSingleton()->special(key, x, y);
        if(_UIspecial)
            _UIspecial(key, x, y);
    }
    void specialup(int key, int x, int y){
        KeyBoard::getSingleton()->specialup(key, x, y);
        if(_UIspecialUp)
            _UIspecialUp(key,x,y);
    }

    void mouse(int button, int state, int x, int y){
        Mouse::getSingleton()->key(button,state,x,y);
        if(_UImouse)
            _UImouse(button,state,x,y);
        if (state == GLUT_UP )
        {
            int wheelDir = 0;
            if ( button == 3 )
            {
                wheelDir = 1;
//                printf("Wheel Up\n");
            }
            else if( button == 4 )
            {
                wheelDir = -1;
//                printf("Wheel Down\n");
            }
            Mouse::getSingleton()->wheel(button, wheelDir, x, y);
            if(_UImouseWheel)
                _UImouseWheel(button, wheelDir, x, y);
        }
    }

    void mousescroll(int button, int dir, int x, int y){
//        cout << "NUKEOGL MWheel" << endl;
        Mouse::getSingleton()->wheel(button,dir,x,y);
        if(_UImouseWheel)
            _UImouseWheel(button,dir,x,y);
    }

    void timer(){
        if(_physTrigger)
            _physTrigger();
    }

    void reshape(int w, int h){
        if(_UIreshape)
            _UIreshape(w,h);

        glViewport(0, 0, w, h);
        this->width = w;
        this->height = h;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov, (GLfloat)w / (GLfloat)h, Near, Far);
        glMatrixMode(GL_MODELVIEW);
    }

    void update(){
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov, (GLfloat)width / (GLfloat)height, Near, Far);
        glMatrixMode(GL_MODELVIEW);
    }

    void initFrameBufferDepthBuffer(void) {

        glGenRenderbuffersEXT(1, &fbo_depth); // Generate one render buffer and store the ID in fbo_depth
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, fbo_depth); // Bind the fbo_depth render buffer

        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height); // Set the render buffer storage to be a depth component, with a width and height of the window

        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, fbo_depth); // Set the render buffer of this buffer to the depth buffer

        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0); // Unbind the render buffer
    }

    void initFrameBufferTexture(void) {
        glGenTextures(1, &fbo_texture); // Generate one texture
        glBindTexture(GL_TEXTURE_2D, fbo_texture); // Bind the texture fbo_texture

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); // Create a standard texture with the width and height of our window

        // Setup the basic texture parameters
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void initFrameBuffer(void) {
        initFrameBufferDepthBuffer(); // Initialize our frame buffer depth buffer

        initFrameBufferTexture(); // Initialize our frame buffer texture

        glGenFramebuffersEXT(1, &fbo); // Generate one frame buffer and store the ID in fbo
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo); // Bind our frame buffer

        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, fbo_texture, 0); // Attach the texture fbo_texture to the color buffer in our frame buffer

        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, fbo_depth); // Attach the depth buffer fbo_depth to our frame buffer

        GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT); // Check that status of our generated frame buffer

        if (status != GL_FRAMEBUFFER_COMPLETE_EXT) // If the frame buffer does not report back as complete
        {
            std::cout << "Couldn't create frame buffer" << std::endl; // Output an error to the console
            exit(0); // Exit the application
        }

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); // Unbind our frame buffer
    }

    int init(int w, int h)
    {
        cout << "Render initialization..." << endl;
        cout << "Render engine: " << getEngine() << endl;
        cout << "NukeOGL version: " << getVersion() << endl;
        this->width = w;
        this->height = h;
        char *myargv [1];
        int myargc=1;
        myargv[0] = strdup("NukeEngine Editor");
        glutInit(&myargc, myargv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
        glutInitWindowPosition(90, 90);
        glutInitWindowSize(w, h);
        glutCreateWindow("NukeEngine Editor");
        glutSetIconTitle("logo.ico");
        cout << get_current_dir_name() << endl;
        glutKeyboardFunc(oglkeyboard);
        glutSpecialFunc(oglspecialkeyboard);
        glutKeyboardUpFunc(oglkeyboardup);
        glutSpecialUpFunc(oglspecialkeyboardup);
        glutCloseFunc(oglclose);
        //glutButtonBoxFunc()
        glutMotionFunc(oglmove);
        glutPassiveMotionFunc(oglpmove);
        glutTimerFunc(30, ogltimer, 1);
        glutMouseFunc(oglmouse);
        glutReshapeFunc(oglreshape);
        glutDisplayFunc(ogldisplay);
        glutIdleFunc(oglidle);
        glutMouseWheelFunc(oglmousescroll);
        glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
        glewInit();

        if(_UIinit)
            _UIinit();

        if(NukeOGL::getSingleton() != this){
            glEnable(GL_TEXTURE_2D); // Enable texturing so we can bind our frame buffer texture
            glEnable(GL_DEPTH_TEST); // Enable depth testing


        }
        initFrameBuffer();

        cout << "Initialization finished" << endl;
        return 0;
    }

    void loop()
    {
        glutMainLoop();
//        while(true){
//            usleep(50);
//            render();
//        }
    }

    void DrawGrid(float HALF_GRID_SIZE)
    {
        float floor=0.0;
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_LINES);
        glColor4f(1.0,1.0,1.0,0.4); /* transparent black -> darker grey */
        for (int v=-HALF_GRID_SIZE;v<=HALF_GRID_SIZE;v++) {
            glVertex3f(v,floor,-HALF_GRID_SIZE);
            glVertex3f(v,floor,+HALF_GRID_SIZE);
            glVertex3f(-HALF_GRID_SIZE,floor,v);
            glVertex3f(+HALF_GRID_SIZE,floor,v);
        }
        glEnd();
    }

    void crosshair (void)
    {
        glDisable(GL_LIGHTING);
        glColor3f(1,0,0);
        glBegin(GL_QUADS);
            glVertex3f(0.0,-1.0,0.0);
            glColor3f(0,1,0);
            glVertex3f(-1000,-1.0,0.0);
            glColor3f(0,0,1);
            glVertex3f(-1000,-1.0,-1000);
            glColor3f(1,1,1);
            glVertex3f(0.0,-1.0,-1000);
        glEnd();
        glEnable(GL_LIGHTING);
    }

    void renderObject(Mesh* mesh, Material* mat, Transform* transform){
        glEnable(GL_COLOR_MATERIAL);
        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT0);

        Vector3 pos = transform->globalPosition();
        Vector3 rot = transform->globalRotation();
        Vector3 scale = (transform->globalScale());
        auto globalScale = glm::vec3(scale.x, scale.y, scale.z);
//        globalScale = glm::rotate(globalScale, (float)tr->rotation.x, {1,0,0});
//        globalScale = glm::rotate(globalScale, (float)tr->rotation.y, {0,1,0});
//        globalScale = glm::rotate(globalScale, (float)tr->rotation.z, {0,0,1});

//        cout << tr->direction().toStringA() << endl;
//        cout << globalScale.x << ", " << globalScale.y << ", " << globalScale.z << endl;
//        cout << scale.x * tr->forward().x << " :: "<< scale.y * tr->forward().y << " :: " << scale.z * tr->forward().z << endl;
        glScaled(globalScale.x, globalScale.y, globalScale.z);
        glRotatef(rot.x, 1.0, 0.0, 0.0);
        glRotatef(rot.y, 0.0, 1.0, 0.0);
        glRotatef(rot.z, 0.0, 0.0, 1.0);
        glTranslated(pos.x, pos.y, pos.z);


        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3,GL_FLOAT,0, mesh->vertexArray);
        glNormalPointer(GL_FLOAT,0,mesh->normalArray);

        glClientActiveTexture(GL_TEXTURE0_ARB);
        glTexCoordPointer(2,GL_FLOAT,0,mesh->uvArray);

        glDrawArrays(GL_TRIANGLES,0,mesh->numVerts);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glTranslated(-pos.x, -pos.y, -pos.z);
        glRotated(-rot.z, 0.0, 0.0, 1.0);
        glRotated(-rot.y, 0.0, 1.0, 0.0);
        glRotated(-rot.x, 1.0, 0.0, 0.0);
        glScaled(1/globalScale.x, 1/globalScale.y, 1/globalScale.z);
    }

    int render()
    {
        //cout << "Render" << endl;
#ifdef EDITOR
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo); // Bind our frame buffer for rendering
        glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT); // Push our glEnable and glViewport states
        DrawGrid(100);
#else
        if(NukeOGL::getSingleton() != this){
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo); // Bind our frame buffer for rendering
            glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT); // Push our glEnable and glViewport states
        }
#endif

        //glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity ();

//        glRotated(transform->rotation.y, 1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
//        glRotated(transform->rotation.x, 0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
//        glTranslated(transform->position.x, transform->position.y, transform->position.z); //translate the screen to the position of our camera

        gluLookAt(transform->position.x,
                          transform->position.y,
                          transform->position.z,
                          transform->position.x + transform->direction().x,
                          transform->position.y + transform->direction().y,
                          transform->position.z + transform->direction().z,
                          0.0,
                          1.0,
                          0.0);

        if(_onRender.size() > 0)
            for(auto _rn : _onRender){
                _rn();
            }

#ifdef EDITOR
        glPopAttrib(); // Restore our glEnable and glViewport states
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); // Unbind our texture
#else
        if(NukeOGL::getSingleton() != this){
            glPopAttrib(); // Restore our glEnable and glViewport states
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); // Unbind our texture
        }
#endif
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(_onGUI.size() > 0)
            for(auto _rn : _onGUI){
                _rn();
            }

        glutSwapBuffers();
        //glutPostRedisplay();
        return 0;
    }

    void deinit()
    {

    }

    char* getEngine()
    {
        return "Open GL 2.1 - glut";
    }

    char* getVersion()
    {
        return "1.0.0";
    }
};

NukeOGL* NukeOGL::_main;

void oglmove(int x, int y){
    NukeOGL::getSingleton()->move(x, y);
}

void oglpmove(int x, int y){
    NukeOGL::getSingleton()->passmove(x, y);
}


void oglkeyboard(unsigned char c, int x, int y) {
    NukeOGL::getSingleton()->keyboard(c,x,y);
}

void oglspecialkeyboard(int key, int x, int y) {
    NukeOGL::getSingleton()->special(key,x,y);
}

void oglkeyboardup(unsigned char c, int x, int y) {
    NukeOGL::getSingleton()->keyboardUp(c,x,y);
}

void oglspecialkeyboardup(int key, int x, int y) {
    NukeOGL::getSingleton()->specialup(key,x,y);
}
void oglmouse (int button, int state, int x, int y) {
    NukeOGL::getSingleton()->mouse(button,state,x,y);
}

void oglmousescroll (int button, int dir, int x, int y) {
//    cout << "OGL MWheel" << endl;
    NukeOGL::getSingleton()->mousescroll(button,dir,x,y);
}


void oglreshape(int width, int height)
{
    NukeOGL::getSingleton()->reshape(width, height);
}

void oglidle(void){
    glutPostRedisplay();
}

void ogldisplay(void)
{
    NukeOGL::getSingleton()->render();
}

void oglclose(){
    NukeOGL::getSingleton()->close();
}

void ogltimer(int t){
    NukeOGL::getSingleton()->timer();
}
#endif // NUKEOGL_H
