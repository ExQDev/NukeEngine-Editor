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
    b::function<void()> _onClose;
    b::function<void()> _physTrigger;
    b::function<void(void)> _onRender;
    b::function<void(void)> _onGUI;

    static NukeOGL* _main;

    GLuint FramebufferName = 0;
    int w,h;
public:
    NukeOGL(){}
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
    GLuint renderedTexture;

    static NukeOGL* getSingleton()
    {
        //static NukeOGL instance;
        if(!_main)
            _main = new NukeOGL();
        return _main;
    }

    void setOnGUI(b::function<void(void)> cb){
        _onGUI = cb;
//        cout << cb << " -- onGUI[" << this << "]" << endl;
    }

    void setOnRender(b::function<void(void)> cb){
        _onRender = cb;
//        cout << cb << " -- onRender" << endl;
    }

    void close()
    {
        if(_onClose)
            _onClose();
    }

    void move(int x, int y)
    {
        //cout << "mov [ " << x << ", " << y << " ]" << endl;
        if(_UImove)
            _UImove(x,y);
    }

    void passmove(int x, int y)
    {
        //cout << "pmov [ " << x << ", " << y << " ]" << endl;
        if(_UImove)
            _UImove(x,y);
    }

    void keyboard(unsigned char c, int x, int y) {
        KeyBoard::getSigleton()->key(c,x,y);
        if(_UIkeyboard)
            _UIkeyboard(c,x,y);
    }
    void keyboardUp(unsigned char c, int x, int y) {
        KeyBoard::getSigleton()->keyup(c,x,y);
        if(_UIkeyaboardUp)
            _UIkeyaboardUp(c,x,y);
    }
    void special(int key, int x, int y){
        KeyBoard::getSigleton()->special(key, x, y);
        if(_UIspecial)
            _UIspecial(key, x, y);
    }
    void specialup(int key, int x, int y){
        KeyBoard::getSigleton()->specialup(key, x, y);
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
        //gluOrtho2D(0, width, 0, height);
        glMatrixMode(GL_MODELVIEW);
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
        glewInit();

        if(_UIinit)
            _UIinit();

        if(NukeOGL::getSingleton() != this){
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_TEST);
            glGenFramebuffers(1, &FramebufferName);
            glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
            glGenTextures(1, &renderedTexture);
            glBindTexture(GL_TEXTURE_2D, renderedTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, renderedTexture, 0);
        }

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

    int render()
    {
        //cout << "Render" << endl;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1.0);

        if(NukeOGL::getSingleton() != this){
           glBindTexture(GL_TEXTURE_2D, renderedTexture);
        }

        if(_onRender)
            _onRender();

        //cout << _onGUI << " -- OnGUI [" << this << "]" << endl;
        if(_onGUI){
            _onGUI();
        }

//        glFlush();

        glutSwapBuffers();
        glutPostRedisplay();

         if(NukeOGL::getSingleton() != this){
            glBindTexture(GL_TEXTURE_2D, 0);
         }
        //cout << "End Render" << endl;
        return 0;
    }

    void deinit()
    {

    }

    char* getEngine()
    {
        return "Open GL";
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
