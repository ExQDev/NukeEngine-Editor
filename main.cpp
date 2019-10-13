#include "API/Model/Include.h"
//#include <API/Model/GameObject.h>
//#include <render/opengl/nukeogl.h>
#include <render/universal/nukebgfx.h>
#include <input/keyboard.h>
#include <config.h>
#include <editor/editorui.h>
#include <interface/Modular.h>
#ifdef EDITOR
#include <interface/EditorInstance.h>
#include <import/assimporter.h>
#else
#include <interface/AppInstance.h>
#endif
#include <lodepng/lodepng.h>

#include <iostream>
using namespace std;

void keyboard1(unsigned char c, int x, int y)
{
//    auto scene = EditorInstance::GetSingleton()->currentScene;
//    for(auto go : scene->hierarchy){
//        if(auto mr = (go->GetComponent<MeshRenderer>())){
//            mr->enabled = !mr->enabled;
//            cout << "[main]\t\t\t" << go->name << "." << mr->name << ".enabled = " << mr->enabled << endl;
//        }
//    }
    //cout << "[main]\t\t\t" << "[1] key pressed! " << c << endl;
}

void keyboard2(unsigned char c, int x, int y)
{
    //cout << "[main]\t\t\t" << "[2] ( " << x << ", " << y << ")" << endl;
}

void special(int key, int x, int y){
//    cout << "[main]\t\t\t" << "[special] ( " << key << ", " << x << ", " << y << ")" << endl;
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
//        cout << "[main]\t\t\t" << "Allocated: " << rent << endl;
//        lodepng::encode(out, rent, w, h);
//        lodepng::save_file(out, "render.png");
    }
}

void specialup(int key, int x, int y){
//    cout << "[main]\t\t\t" << "[special UP] ( " << key << ", " << x << ", " << y << ")" << endl;
}

//void testRender(NukeOGL *gl){
//    cout << "[main]\t\t\t" << "=========== Render callbacks addresses[" << gl << "] ==============" << endl;
//    cout << "[main]\t\t\t" << gl->_UIinit << endl;
//    cout << "[main]\t\t\t" << gl->_UIkeyaboardUp << endl;
//    cout << "[main]\t\t\t" << gl->_UIkeyboard << endl;
//    cout << "[main]\t\t\t" << gl->_UImouse << endl;
//    cout << "[main]\t\t\t" << gl->_UImove << endl;
//    cout << "[main]\t\t\t" << gl->_UIpmove << endl;
//    cout << "[main]\t\t\t" << gl->_UIreshape << endl;
//    cout << "[main]\t\t\t" << gl->_UIspecial << endl;
//    cout << "[main]\t\t\t" << gl->_UIspecialUp << endl;
//    cout << "[main]\t\t\t" << "=============================== END ================================" << endl;
//}

std::string MultiString(std::string str, int times){
    std::string out = "";
    for(int i = 0; i < times; i++){
        out += str;
    }
    return out;
}

void PrintHierarchy(GameObject* go, int level){
	if (!go)
		return;

    cout << "[main]\t\t\t" << MultiString("\t", level) << go->name << "\t(parentgpos: " << (go->parent ? go->parent->transform.globalPosition().toStringA() : "null") << ")" << ";; POS: " << go->transform.globalPosition().toStringA() << endl;
    if(go->children.size() > 0)
        for(auto child : go->children)
            PrintHierarchy(child, level + 1);
    else
        cout << "[main]\t\t\t" << MultiString("\t", level + 1) << "No children" << endl;
    if(go->components.size() > 0)
        for(auto cmp : go->components)
            cout << "[main]\t\t\t" << MultiString("\t", level + 1) << "+" << cmp->name << endl;
}

void CreateDemoObjects(){
    GameObject* root = new GameObject("root");
    GameObject* subroot = new GameObject("subroot");
    GameObject* secsubroot = new GameObject("2 subroot");
    GameObject* deepObject = new GameObject("Deep object");
    deepObject->SetParent(subroot);
    subroot->SetParent(root);
    secsubroot->SetParent(root);
    EditorInstance::GetSingleton()->currentScene->hierarchy->push_back(root);
}

void InitEngine()
{
	cout << "[main]\t\t\t" << "Engine initialization..." << endl;
	cout << "[main]\t\t\t" << "Editor is: " << EditorInstance::GetSingleton() << endl;
	cout << "[main]\t\t\t" << "Current scene is: " << EditorInstance::GetSingleton()->currentScene << endl;
	cout << "[main]\t\t\t" << "Hierarchy: " << EditorInstance::GetSingleton()->currentScene->hierarchy << endl;
    if (EditorInstance::GetSingleton()->currentScene->hierarchy->empty())
    {
        GameObject* edcam = new GameObject("Editor Camera");
        iRender* rnd = NukeBGFX::getSingleton();
        Camera* edcamc = new Camera(edcam, rnd);
        edcamc->transform->position = { 0, 10, -10};
        edcamc->freeMode = true;
        //edcamc->Init(edcam);
        edcam->layer = NUKEE_LAYER_EDITOR;
        EditorInstance::GetSingleton()->currentScene->hierarchy->push_back(edcam);
        //edcamc->renderer->currentScene = EditorInstance::GetSingleton()->currentScene;
    }
	cout << "[main]\t\t\t" << "New hierarchy size: " << EditorInstance::GetSingleton()->currentScene->hierarchy->size() << endl;
	cout << "[main]\t\t\t" << "Editor camera: " << EditorInstance::GetSingleton()->currentScene->Get("Editor Camera") << endl;
    EditorInstance::GetSingleton()->StartUpdateThread();
	cout << "[main]\t\t\t" << "Update is bootstraped. Next stage..." << endl;
}

void Unload()
{
#ifdef WIN32
	Sleep(1000);
#else
    usleep(1000);
#endif // WIN32
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
        goc->Update<MeshRenderer>();
    }
}

void RenderScene(){
    auto scene = EditorInstance::GetSingleton()->currentScene;
    for(auto go : *scene->hierarchy){
        RenderObject(go);
        if(auto mr = (go->GetComponent<Camera>())){
            mr->Update();
        }
    }
}

iRender* PreInitRender(){
	cout << "[main]\t\t\t" << "Render preinit..." << endl;

    iRender * render = NukeBGFX::getSingleton();

	cout << "[main]\t\t\t" << "Renderer is: " << render << endl;
    auto gl = (NukeBGFX*)render;
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

    render->setOnRender(RenderScene);
    render->setOnGUI(editorDraw);

	cout << "[main]\t\t\t" << "Preinit done... Next stage..." << endl;

    return render;
}

void InitInput(KeyBoard *keyboard){
	cout << "[main]\t\t\t" << "Init input..." << endl;
    *keyboard += keyboard1;
    *keyboard &= keyboard2;
    *keyboard *= special;
    *keyboard |= specialup;
	cout << "[main]\t\t\t" << "Done!... Next stage..." << endl;
}


int main()
{
	cout << "[main]\t\t\t" << "NukeEngine starting... Welcome!" << endl;
	InitEngine();
	iRender* render = PreInitRender();
    Config* config = Config::getSingleton();
	EditorInstance* instance = EditorInstance::GetSingleton();
	instance->config = config;
	instance->keyboard = KeyBoard::getSingleton();
	instance->mouse = Mouse::getSingleton();

   
	InitInput(instance->keyboard);
    render->init(config->window.w, config->window.h);
    cout << "[main]\t\t\t" << "> Render: " << render << endl;

	cout << "[main]\t\t\t" << "Modules initialization..." << endl;
    InitModules(instance);

    //CreateDemoObjects();
    //cubepositions();
	cout << "[main]\t\t\t" << "Done! Importing model..." << endl;

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
//            cout << "[main]\t\t\t" << go->name << " : " << go->transform.position.toStringA() << endl;
//            EditorInstance::GetSingleton()->currentScene->Add(go);
//        }
    }

	cout << "[main]\t\t\t" << "Hierarchy: " << EditorInstance::GetSingleton()->currentScene->hierarchy << endl;
	if(EditorInstance::GetSingleton()->currentScene->hierarchy->size() > 0)
		for(auto g : *EditorInstance::GetSingleton()->currentScene->hierarchy)
			if(g)
				PrintHierarchy(g, 0);

	cout << "[main]\t\t\t" << "All done. Starting render loop." << endl;

    render->loop();

    cout << "[main]\t\t\t" << "shit down..." << endl;
    Unload();
    render->deinit();
    return 0;
}
