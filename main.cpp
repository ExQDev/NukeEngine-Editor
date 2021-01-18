#include <API/Model/GameObject.h>
//#include <render/opengl/nukeogl.h>
#include <render/universal/nukebgfx.h>
#include <input/keyboard.h>
#include <config.h>
#include <editor/editorui.h>
#include <interface/Modular.h>
#ifdef EDITOR
#include <interface/AppInstance.h>
#include <import/assimporter.h>
#else
#include <interface/AppInstance.h>
#endif
#include <lodepng/lodepng.h>

#include <iostream>
using namespace std;

void CreateDemoObjects(){
    GameObject* root = new GameObject("root");
    GameObject* subroot = new GameObject("subroot");
    GameObject* secsubroot = new GameObject("2 subroot");
    GameObject* deepObject = new GameObject("Deep object");
    deepObject->SetParent(subroot);
    subroot->SetParent(root);
    secsubroot->SetParent(root);
    AppInstance::GetSingleton()->currentScene->GetHierarchy().push_back(root);
}

int main() {
	AppInstance* app = AppInstance::GetSingleton();
	app->setEditor(true);
	Scene* nScene = new Scene();
	app->currentScene = nScene;
    iRender* render = NukeBGFX::getSingleton();
	Config* conf = Config::getSingleton();
	
	/*if (app->currentScene->GetHierarchy().empty())
    {*/
        GameObject* edcam = new GameObject("Editor Camera");
        cout << "[main]\t\t\t" << "Camera render is: " << render << endl;
        Camera* edcamc = new Camera(edcam, render);
        edcamc->transform->position = { 0, 10, -10};
        edcamc->freeMode = true;
        edcam->layer = Layer::L_EDITOR;
        app->currentScene->GetHierarchy().push_back(edcam);
    //}
	cout << "[main]\t\t\t" << "New hierarchy size: " << app->currentScene->GetHierarchy().size() << endl;
	GameObject* editorCam = app->currentScene->Get("Editor Camera");
	cout << "[main]\t\t\t" << "Editor camera: " << editorCam << endl;
	
	render->_UIinit = editorinit;
    render->_UIkeyaboardUp = editorkeyaboardUp;
    render->_UIkeyboard = editorkeyboard;
    render->_UImouse = editormouse;
    render->_UImouseWheel = editormousewheel;
	render->_UImove = editormove;
	render->_UIpmove = editorpmove;
	render->_UIreshape = editorreshape;
	render->_UIspecial = editorspecial;
	render->_UIspecialUp = editorspecialUp;

    //render->setOnRender(RenderScene);
    render->setOnGUI(editorDraw);

	render->init(conf->window.w, conf->window.h);
	render->loop();
	UnloadModules();
	render->deinit();
	return 0;
}

//void keyboard1(unsigned char c, int x, int y)
//{
////    auto scene = AppInstance::GetSingleton()->currentScene;
////    for(auto go : scene->hierarchy){
////        if(auto mr = (go->GetComponent<MeshRenderer>())){
////            mr->enabled = !mr->enabled;
////            cout << "[main]\t\t\t" << go->name << "." << mr->name << ".enabled = " << mr->enabled << endl;
////        }
////    }
//    //cout << "[main]\t\t\t" << "[1] key pressed! " << c << endl;
//}
//
//void keyboard2(unsigned char c, int x, int y)
//{
//    //cout << "[main]\t\t\t" << "[2] ( " << x << ", " << y << ")" << endl;
//}
//
//void special(int key, int x, int y){
////    cout << "[main]\t\t\t" << "[special] ( " << key << ", " << x << ", " << y << ")" << endl;
//    if(key == 11)
//    {
//        glutFullScreenToggle();
//    }
//    if(key == 12)
//    {
////        std::vector<unsigned char> out;
////        auto renTex = (NukeOGL::getSingleton()->getRenderTexture());
////        int w = NukeOGL::getSingleton()->width;
////        int h = NukeOGL::getSingleton()->height;
////        unsigned char *rent = (unsigned char*)malloc(sizeof(unsigned char) * w * h * 3);
////        void* rt = renTex;
////        memcpy(rent, rt, 3*h*w);
////        cout << "[main]\t\t\t" << "Allocated: " << rent << endl;
////        lodepng::encode(out, rent, w, h);
////        lodepng::save_file(out, "render.png");
//    }
//}
//
//void specialup(int key, int x, int y){
////    cout << "[main]\t\t\t" << "[special UP] ( " << key << ", " << x << ", " << y << ")" << endl;
//}
//
////void testRender(NukeOGL *gl){
////    cout << "[main]\t\t\t" << "=========== Render callbacks addresses[" << gl << "] ==============" << endl;
////    cout << "[main]\t\t\t" << gl->_UIinit << endl;
////    cout << "[main]\t\t\t" << gl->_UIkeyaboardUp << endl;
////    cout << "[main]\t\t\t" << gl->_UIkeyboard << endl;
////    cout << "[main]\t\t\t" << gl->_UImouse << endl;
////    cout << "[main]\t\t\t" << gl->_UImove << endl;
////    cout << "[main]\t\t\t" << gl->_UIpmove << endl;
////    cout << "[main]\t\t\t" << gl->_UIreshape << endl;
////    cout << "[main]\t\t\t" << gl->_UIspecial << endl;
////    cout << "[main]\t\t\t" << gl->_UIspecialUp << endl;
////    cout << "[main]\t\t\t" << "=============================== END ================================" << endl;
////}
//
//void CreateDemoObjects(){
//    GameObject* root = new GameObject("root");
//    GameObject* subroot = new GameObject("subroot");
//    GameObject* secsubroot = new GameObject("2 subroot");
//    GameObject* deepObject = new GameObject("Deep object");
//    deepObject->SetParent(subroot);
//    subroot->SetParent(root);
//    secsubroot->SetParent(root);
//    AppInstance::GetSingleton()->currentScene->GetHierarchy().push_back(root);
//}
//
//std::string MultiString(std::string str, int times) {
//	std::string out = "";
//	for (int i = 0; i < times; i++) {
//		out += str;
//	}
//	return out;
//}
//
//void PrintHierarchy(GameObject* go, int level) {
//	if (!go)
//		return;
//	//GameObject* goo = go;
//	cout << "[AppInstance]\t"
//		<< MultiString("\t", level)
//		<< go->GetName()
//		<< "\t(parentgpos: "
//		<< (go->GetParent() ? go->GetParent()->GetTransform().globalPosition().toStringA() : "null")
//		<< ")"
//		<< ";; POS: "
//		<< go->GetTransform().globalPosition().toStringA()
//		<< endl;
//
//	if (go->children.size() > 0)
//		for (auto child : go->children)
//			PrintHierarchy(child, level + 1);
//	else
//		cout << "[AppInstance]\t" << MultiString("\t", level + 1) << "No children" << endl;
//	if (go->components.size() > 0)
//		for (auto cmp : go->components)
//			cout << "[AppInstance]\t" << MultiString("\t", level + 1) << "+" << cmp->name << endl;
//}
//
//void InitEngine()
//{
//	cout << "[main]\t\t\t" << "Engine initialization..." << endl;
//	cout << "[main]\t\t\t" << "Editor is: " << AppInstance::GetSingleton() << endl;
//	cout << "[main]\t\t\t" << "Current scene is: " << AppInstance::GetSingleton()->currentScene << endl;
//	cout << "[main]\t\t\t" << "Hierarchy: " << &AppInstance::GetSingleton()->currentScene->GetHierarchy() << endl;
//	AppInstance* instance = AppInstance::GetSingleton();
//    if (instance->currentScene->GetHierarchy().empty())
//    {
//        GameObject* edcam = new GameObject("Editor Camera");
//        iRender* rnd = NukeBGFX::getSingleton();
//		cout << "[main]\t\t\t" << "Camera render is: " << rnd << endl;
//        Camera* edcamc = new Camera(edcam, rnd);
//        edcamc->transform->position = { 0, 10, -10};
//        edcamc->freeMode = true;
//        //edcamc->Init(edcam);
//        edcam->layer = NUKEE_LAYER_EDITOR;
//        AppInstance::GetSingleton()->currentScene->GetHierarchy().push_back(edcam);
//        //edcamc->renderer->currentScene = AppInstance::GetSingleton()->currentScene;
//    }
//	cout << "[main]\t\t\t" << "New hierarchy size: " << instance->currentScene->GetHierarchy().size() << endl;
//	cout << "[main]\t\t\t" << "Editor camera: " << instance->currentScene->Get("Editor Camera") << endl;
//}
//
//void Unload()
//{
//#ifdef WIN32
//	Sleep(1000);
//#else
//    usleep(1000);
//#endif // WIN32
//    UnloadModules();
//}
//
////positions of the cubes
//float positionz[10];
//float positionx[10];
//
//void cubepositions (void) { //set the positions of the cubes
//
//    for (int i=0;i<10;i++)
//    {
//    positionz[i] = rand()%5 + 5;
//    positionx[i] = rand()%5 + 5;
//    }
//}
//
//void cube (void) {
//    for (int i=0;i<10;i++)
//    {
//    glPushMatrix();
//    glTranslated(-positionx[i + 1] * 10, 0, -positionz[i + 1] *
//10); //translate the cube
//    glutSolidCube(2); //draw the cube
//    glPopMatrix();
//    }
//}
//
//void RenderObject(GameObject* go){
//    for(auto goc : go->children)
//    {
//        goc->Update<MeshRenderer>();
//    }
//}
//
//void RenderScene(){
//    auto scene = AppInstance::GetSingleton()->currentScene;
//    for(auto go : scene->GetHierarchy()){
//        RenderObject(go);
//        if(auto mr = (go->GetComponent<Camera>())){
//            mr->Update();
//        }
//    }
//}
//
//iRender* PreInitRender(){
//	cout << "[main]\t\t\t" << "Render preinit..." << endl;
//
//    iRender * render = NukeBGFX::getSingleton();
//
//	cout << "[main]\t\t\t" << "Renderer is: " << render << endl;
//    //auto gl = (NukeBGFX*)render;
//    render->_UIinit = editorinit;
//    render->_UIkeyaboardUp = editorkeyaboardUp;
//    render->_UIkeyboard = editorkeyboard;
//    render->_UImouse = editormouse;
//    render->_UImouseWheel = editormousewheel;
//	render->_UImove = editormove;
//	render->_UIpmove = editorpmove;
//	render->_UIreshape = editorreshape;
//	render->_UIspecial = editorspecial;
//	render->_UIspecialUp = editorspecialUp;
//
//    render->setOnRender(RenderScene);
//    render->setOnGUI(editorDraw);
//
//	cout << "[main]\t\t\t" << "Preinit done... Next stage..." << endl;
//
//    return render;
//}
//
//void InitInput(KeyBoard *keyboard){
//	cout << "[main]\t\t\t" << "Init input..." << endl;
//    *keyboard += keyboard1;
//    *keyboard &= keyboard2;
//    *keyboard *= special;
//    *keyboard |= specialup;
//	cout << "[main]\t\t\t" << "Done!... Next stage..." << endl;
//}
//
//
//int main()
//{
//	AppInstance* instance = AppInstance::GetSingleton();
//	instance->setEditor(true);
//	cout << "[main]\t\t\t" << "NukeEngine starting... Welcome!" << endl;
//	InitEngine();
//	iRender* render = PreInitRender();
//	cout << "[main]\t\t\t" << "Preinited render is: " << render << endl;
//    Config* config = Config::getSingleton();
//	
//	instance->config = config;
//	instance->keyboard = KeyBoard::getSingleton();
//	instance->mouse = Mouse::getSingleton();
//
//   
//	InitInput(instance->keyboard);
//	cout << "[main]\t\t\t" << ">> Window size: w(" << config->window.w << "), h(" << config->window.h << ")" << endl;
//    render->init(config->window.w, config->window.h);
//    cout << "[main]\t\t\t" << "> Render: " << render << endl;
//
//	cout << "[main]\t\t\t" << "Modules initialization..." << endl;
//    InitModules(instance);
//
//    //CreateDemoObjects();
//    //cubepositions();
//	cout << "[main]\t\t\t" << "Done! Importing model..." << endl;
//
//    AssImporter::getSingleton()->Import("mpm_vol.09_p35.OBJ");
//    if(ResDB::getSingleton()->prefabs.size() > 0)
//    {
//        for(auto pref : ResDB::getSingleton()->prefabs){
//            AppInstance::GetSingleton()->currentScene->Add(pref);
//        }
////        for(auto m : ResDB::getSingleton()->meshes){
////            GameObject* go = new GameObject(m->name);
////            MeshRenderer* mr = new MeshRenderer();
////            mr->mesh = m;
////            go->AddComponent(mr);//dynamic_cast<Component*>(mr));
////            cout << "[main]\t\t\t" << go->name << " : " << go->transform.position.toStringA() << endl;
////            AppInstance::GetSingleton()->currentScene->Add(go);
////        }
//    }
//
//	cout << "[main]\t\t\t" << "Hierarchy: " << &AppInstance::GetSingleton()->currentScene->GetHierarchy() << endl;
//	/*if(AppInstance::GetSingleton()->currentScene->GetHierarchy().size() > 0)
//		for(auto g : AppInstance::GetSingleton()->currentScene->GetHierarchy())
//			if(g)
//				PrintHierarchy(g, 0);*/
//
//	cout << "[main]\t\t\t" << "All done. Starting render loop." << endl;
//
//	//AppInstance::GetSingleton()->StartUpdateThread();
//	cout << "[main]\t\t\t" << "Update is bootstraped. Next stage..." << endl;
//    render->loop();
//
//    cout << "[main]\t\t\t" << "shit down..." << endl;
//    Unload();
//    render->deinit();
//    return 0;
//}
