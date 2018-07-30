#include <iostream>
#include <render/opengl/nukeogl.h>
#include <input/keyboard.h>
#include <config.h>
#include <editor/editorui.h>
#ifdef EDITOR
#include <interface/EditorInstance.h>
#else
#include <API/Model/AppInstance.h>
#endif

using namespace std;

void keyboard1(unsigned char c, int x, int y)
{
//    cout << "[1] key pressed! " << c << endl;
}

void keyboard2(unsigned char c, int x, int y)
{
//    cout << "[2] ( " << x << ", " << y << ")" << endl;
}

void special(int key, int x, int y){
//    cout << "[special] ( " << key << ", " << x << ", " << y << ")" << endl;
    if(key == 11)
    {
        glutFullScreenToggle();
    }
}

void specialup(int key, int x, int y){
//    cout << "[special UP] ( " << key << ", " << x << ", " << y << ")" << endl;
}

void testRender(NukeOGL *gl){
    cout << "=========== Render callbacks addresses[" << gl << "] ==============" << endl;
    cout << gl->_UIinit << endl;
    cout << gl->_UIkeyaboardUp << endl;
    cout << gl->_UIkeyboard << endl;
    cout << gl->_UImouse << endl;
    cout << gl->_UImove << endl;
    cout << gl->_UIpmove << endl;
    cout << gl->_UIreshape << endl;
    cout << gl->_UIspecial << endl;
    cout << gl->_UIspecialUp << endl;
    cout << "=============================== END ================================" << endl;
}
int main()
{
    iRender * render = NukeOGL::getSingleton();
    KeyBoard* keyboard = KeyBoard::getSigleton();
    Config* config = Config::getSingleton();
    *keyboard += keyboard1;
    *keyboard &= keyboard2;
    *keyboard *= special;
    *keyboard |= specialup;
    auto gl = (NukeOGL*)render;

//    testRender(gl);

    gl->_UIinit = editorinit;
    gl->_UIkeyaboardUp = editorkeyaboardUp;
    gl->_UIkeyboard = editorkeyboard;
    gl->_UImouse = editormouse;
    gl->_UImove = editormove;
    gl->_UIpmove = editorpmove;
    gl->_UIreshape = editorreshape;
    gl->_UIspecial = editorspecial;
    gl->_UIspecialUp = editorspecialUp;

//    testRender(gl);

    render->setOnGUI(editorDraw);
    render->init(config->window.w, config->window.h);
    cout << "shit down..." << endl;
    return 0;
}
