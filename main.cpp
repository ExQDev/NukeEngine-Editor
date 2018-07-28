#include <iostream>
#include <render/opengl/nukeogl.h>
#include <input/keyboard.h>
#include <backend/lua.h>
#include <gui/gui.h>
#include <config.h>

using namespace std;

void keyboard1(unsigned char c, int x, int y)
{
    cout << "[1] key pressed! " << c << endl;
}

void keyboard2(unsigned char c, int x, int y)
{
    cout << "[2] ( " << x << ", " << y << ")" << endl;
}

void special(int key, int x, int y){
    cout << "[special] ( " << key << ", " << x << ", " << y << ")" << endl;
    if(key == 11)
    {
        glutFullScreenToggle();
    }
}

void specialup(int key, int x, int y){
    cout << "[special UP] ( " << key << ", " << x << ", " << y << ")" << endl;
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
    cout << config->window.w << ", " << config->window.h << endl;
    render->init(config->window.w, config->window.h);
    cout << "shit down..." << endl;
    return 0;
}
