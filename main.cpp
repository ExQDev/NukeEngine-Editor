#include <iostream>
#include <render/opengl/nukeogl.h>

using namespace std;


int main()
{
    iRender * render = NukeOGL::getSingleton();
    render->init(1280, 720);
    cout << "shit down..." << endl;
    return 0;
}
