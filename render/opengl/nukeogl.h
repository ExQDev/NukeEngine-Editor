#ifndef NUKEOGL_H
#define NUKEOGL_H
#include "../irender.h"
#include "../../input/keyboard.h"
#include "../../input/keyboard.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <boost/thread.hpp>
#include <iostream>

using namespace std;

void oglkeyboard(unsigned char c, int x, int y);
void oglmouse (int button, int state, int x, int y);
void oglreshape(int width, int height);
void oglidle(void);
void ogldisplay(void);


class NukeOGL : public iRender
{
private:
    NukeOGL(){}
    ~NukeOGL(){}

public:
    static NukeOGL* getSingleton()
    {
        static NukeOGL instance;
        return &instance;
    }

    void keyboard(unsigned char c, int x, int y) {
        cout << "Key pressed! [" << c << "]" << endl;
        KeyBoard::getSigleton()->key(c,x,y);
    //    if (c == 27) {
    //        cout << "Escape pressed!" << endl;
    //        exit(0);
    //    }
    }

    void mouse(int button, int state, int x, int y){
        cout << "Mouse event! [" << button << ", " << state << ", " << x << ", " << y << "]" << endl;
    //    if (button == GLUT_RIGHT_BUTTON) {
    //        cout << "CLUT Right button pressed!" << endl;
    //        exit(0);
    //    }
    }

    int init(int w, int h)
    {
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
        glutMouseFunc(oglmouse);
        glutReshapeFunc(oglreshape);
        glutDisplayFunc(ogldisplay);
        glutIdleFunc(oglidle);
        glewInit();

        glutMainLoop();
        return 0;
    }

    void loop()
    {
        while(true){
            usleep(50);
            render();
        }
    }

    int render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1.0);

        glFlush();
        glutSwapBuffers();
        glutPostRedisplay();
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

void oglkeyboard(unsigned char c, int x, int y) {
    NukeOGL::getSingleton()->keyboard(c,x,y);
}

void oglmouse (int button, int state, int x, int y) {
    NukeOGL::getSingleton()->mouse(button,state,x,y);
}

void oglreshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

void oglidle(void){
    glutPostRedisplay();
}

void ogldisplay(void)
{
    NukeOGL::getSingleton()->render();
}

#endif // NUKEOGL_H
