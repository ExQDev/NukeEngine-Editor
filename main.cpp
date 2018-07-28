#include <iostream>
#include <render/opengl/nukeogl.h>
#include <input/keyboard.h>

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
    if(key == 2)
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
    *keyboard += keyboard1;
    *keyboard &= keyboard2;
    *keyboard *= special;
    *keyboard |= specialup;
    render->init(1280, 720);
    cout << "shit down..." << endl;
    return 0;
}
