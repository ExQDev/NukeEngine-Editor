#include <iostream>
#include <API/Model/Include.h>
#include <render/opengl/nukeogl.h>
#include <input/keyboard.h>
#include <config.h>
#include <editor/editorui.h>
#include <interface/Modular.h>
#ifdef EDITOR
#include <interface/EditorInstance.h>
#include <import/assimporter.h>
#else
#include <API/Model/AppInstance.h>
#endif
#include <deps/lodepng/lodepng.h>

using namespace std;

void keyboard1(unsigned char c, int x, int y)
{
//    auto scene = EditorInstance::GetSingleton()->currentScene;
//    for(auto go : scene->hierarchy){
//        if(auto mr = (go->GetComponent<MeshRenderer>())){
//            mr->enabled = !mr->enabled;
//            cout << go->name << "." << mr->name << ".enabled = " << mr->enabled << endl;
//        }
//    }
    //cout << "[1] key pressed! " << c << endl;
}

void keyboard2(unsigned char c, int x, int y)
{
    //cout << "[2] ( " << x << ", " << y << ")" << endl;
}

void special(int key, int x, int y){
//    cout << "[special] ( " << key << ", " << x << ", " << y << ")" << endl;
    if(key == 11)
    {
        glutFullScreenToggle();
    }
    if(key == 12)
    {
//        std::vector<unsigned char> out;
//        auto renTex = (NukeOGL::getSingleton()->getRenderTexture());
//        int w = NukeOGL::getSingleton()->width;
//        int h = NukeOGL::getSingleton()->height;
//        unsigned char *rent = (unsigned char*)malloc(sizeof(unsigned char) * w * h * 3);
//        void* rt = renTex;
//        memcpy(rent, rt, 3*h*w);
//        cout << "Allocated: " << rent << endl;
//        lodepng::encode(out, rent, w, h);
//        lodepng::save_file(out, "render.png");
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
    cout << MultiString("\t", level) << go->name << "\t(parentgpos: " << (go->parent ? go->parent->transform.globalPosition().toStringA() : "null") << ")" << ";; POS: " << go->transform.globalPosition().toStringA() << endl;
    if(go->children.size() > 0)
        for(auto child : go->children)
            PrintHierarchy(child, level + 1);
    else
        cout << MultiString("\t", level + 1) << "No children" << endl;
    if(go->components.size() > 0)
        for(auto cmp : go->components)
            cout << MultiString("\t", level + 1) << "+" << cmp->name << endl;
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
        edcamc->transform->position = { 0, 10, -10};
        edcamc->freeMode = true;
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

//positions of the cubes
float positionz[10];
float positionx[10];

void cubepositions (void) { //set the positions of the cubes

    for (int i=0;i<10;i++)
    {
    positionz[i] = rand()%5 + 5;
    positionx[i] = rand()%5 + 5;
    }
}

void cube (void) {
    for (int i=0;i<10;i++)
    {
    glPushMatrix();
    glTranslated(-positionx[i + 1] * 10, 0, -positionz[i + 1] *
10); //translate the cube
    glutSolidCube(2); //draw the cube
    glPopMatrix();
    }
}

void RenderObject(GameObject* go){
    for(auto goc : go->children)
    {
        //b::function<void(Mesh* mesh, Material* mat, Transform* transform)> cb = b::bind(b::mem_fn(&iRender::renderObject), iRender::getSingleton(), _1, _2, _3);
        //goc->GetComponent<MeshRenderer>()->SetRenderCalback(cb);
        goc->Update<MeshRenderer>();//RenderObject(goc);
    }
}

void RenderScene(){
    auto scene = EditorInstance::GetSingleton()->currentScene;
    for(auto go : scene->hierarchy){
        RenderObject(go);
        if(auto mr = (go->GetComponent<Camera>())){
            mr->Update();
        }
    }
}



int main()
{
    iRender * render = NukeOGL::getSingleton();
    KeyBoard* keyboard = KeyBoard::getSingleton();
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
    render->setOnRender(RenderScene);
    render->setOnGUI(editorDraw);
    render->init(config->window.w, config->window.h);

    InitEngine();
    cout << "> Render: " << render << endl;
    InitModules(EditorInstance::GetSingleton());
    CreateDemoObjects();
    cubepositions();



    AssImporter::getSingleton()->Import("mpm_vol.09_p35.OBJ");
    if(ResDB::getSingleton()->prefabs.size() > 0)
    {
        for(auto pref : ResDB::getSingleton()->prefabs){
            EditorInstance::GetSingleton()->currentScene->Add(pref);
        }
//        for(auto m : ResDB::getSingleton()->meshes){
//            GameObject* go = new GameObject(m->name);
//            MeshRenderer* mr = new MeshRenderer();
//            mr->mesh = m;
//            go->AddComponent(mr);//dynamic_cast<Component*>(mr));
//            cout << go->name << " : " << go->transform.position.toStringA() << endl;
//            EditorInstance::GetSingleton()->currentScene->Add(go);
//        }
    }


    for(auto g : EditorInstance::GetSingleton()->currentScene->hierarchy)
        PrintHierarchy(g, 0);

    render->loop();

    cout << "shit down..." << endl;
    Unload();
    render->deinit();
    return 0;
}
