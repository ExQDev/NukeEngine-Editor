#ifndef NUKEOGL_H
#define NUKEOGL_H
#include "../irender.h"
#include "../../input/keyboard.h"
#include "../../input/mouse.h"
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
    NukeOGL(){}
    ~NukeOGL(){}
    b::function<void()> _onClose;
    b::function<void()> _physTrigger;
    b::function<void(void)> _onRender;
    b::function<void(void)> _onGUI;



public:
    b::function<void()> _UIinit;
    b::function<void(unsigned char c, int x, int y)> _UIkeyboard;
    b::function<void(unsigned char c, int x, int y)> _UIkeyaboardUp;
    b::function<void(int key, int x, int y)> _UIspecial;
    b::function<void(int key, int x, int y)> _UIspecialUp;
    b::function<void(int button, int state, int x, int y)> _UImouse;
    b::function<void(int x, int y)> _UImove;
    b::function<void(int x, int y)> _UIpmove;
    b::function<void(int w, int h)> _UIreshape;

    static NukeOGL* getSingleton()
    {
        static NukeOGL instance;
        return &instance;
    }

    void setOnGUI(b::function<void(void)> cb){
        _onGUI = cb;
    }

    void setOnRender(b::function<void(void)> cb){
        _onRender = cb;
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
    }

    void timer(){
        if(_physTrigger)
            _physTrigger();
    }

    void reshape(int w, int h){
        if(_UIreshape)
            _UIreshape(w,h);

        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //gluOrtho2D(0, width, 0, height);
        glMatrixMode(GL_MODELVIEW);
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
        glewInit();

        if(_UIinit)
            _UIinit();

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

        if(_onRender)
            _onRender();

        if(_onGUI)
            _onGUI();

//        glFlush();
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
