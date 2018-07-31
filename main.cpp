#include <iostream>
#include <render/opengl/nukeogl.h>
#include <input/keyboard.h>
#include <config.h>
#include <editor/editorui.h>
#include <interface/Modular.h>
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

std::string MultiString(std::string str, int times){
    std::string out = "";
    for(int i = 0; i < times; i++){
        out += str;
    }
    return out;
}

void PrintHierarchy(GameObject* go, int level){
    cout << MultiString("\t", level) << go->name << endl;
    if(go->children.size() > 0)
        for(auto child : go->children)
            PrintHierarchy(child, level + 1);
    else
        cout << MultiString("\t", level + 1) << "No children" << endl;
}

void CreateDemoObjects(){
    GameObject* root = new GameObject("root");
    GameObject* subroot = new GameObject("subroot");
    GameObject* secsubroot = new GameObject("2 subroot");
    GameObject* deepObject = new GameObject("Deep object");
    deepObject->SetParent(subroot);
    subroot->SetParent(root);
    secsubroot->SetParent(root);
    EditorInstance::GetSingleton()->currentScene->hierarchy.push_back(root);
}

void InitEngine()
{
    if (EditorInstance::GetSingleton()->currentScene->hierarchy.empty())
    {
        GameObject* edcam = new GameObject("Editor Camera");
        iRender* rnd = NukeOGL::getSingleton();
        Camera* edcamc = new Camera(edcam, rnd);
        //edcamc->Init(edcam);
        edcam->layer = NUKEE_LAYER_EDITOR;
        EditorInstance::GetSingleton()->currentScene->hierarchy.push_back(edcam);
        //edcamc->renderer->currentScene = EditorInstance::GetSingleton()->currentScene;
    }
    EditorInstance::GetSingleton()->StartUpdateThread();
}

void Unload()
{
    usleep(1000);
    UnloadModules();
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
    gl->_UImouseWheel = editormousewheel;
    gl->_UImove = editormove;
    gl->_UIpmove = editorpmove;
    gl->_UIreshape = editorreshape;
    gl->_UIspecial = editorspecial;
    gl->_UIspecialUp = editorspecialUp;
//    testRender(gl);
    render->setOnGUI(editorDraw);
    render->init(config->window.w, config->window.h);

    InitEngine();
    InitModules(EditorInstance::GetSingleton());
    CreateDemoObjects();

    for(auto g : EditorInstance::GetSingleton()->currentScene->hierarchy)
        PrintHierarchy(g, 0);


    render->loop();
    cout << "shit down..." << endl;
    Unload();
    render->deinit();
    return 0;
}
