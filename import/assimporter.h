#ifndef ASSIMPORTER_H
#define ASSIMPORTER_H
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <API/Model/resdb.h>
#include <API/Model/MeshRenderer.h>

using namespace std;

class AssImporter
{
    AssImporter() {}
    ~AssImporter() {}

    GameObject* ImportObject(aiNode* node, const aiScene* scene){
        ResDB* res = ResDB::getSingleton();
        auto go = new GameObject(node->mName.C_Str());
        for(int i = 0; i < node->mNumMeshes; i++){
            auto cmesh = node->mMeshes[i];
            GameObject* ngo = new GameObject(scene->mMeshes[cmesh]->mName.C_Str());
            Mesh* m = new Mesh();
            m->ImportAIMesh(scene->mMeshes[cmesh]);
            res->meshes.push_back(m);

            Material* mat = new Material();
            mat->ImportAiMaterial(scene->mMaterials[scene->mMeshes[cmesh]->mMaterialIndex]);
            ResDB::getSingleton()->materials.push_back(mat);

            MeshRenderer* mr = new MeshRenderer();
            mr->mesh = m;
            mr->mat = mat;
            ngo->AddComponent(mr);
            go->AddChild(ngo);
        }
        for(int i = 0; i < node->mNumChildren; i++){
            go->AddChild(ImportObject(node->mChildren[i], scene));
        }
        return go;
    }
public:
    static AssImporter* getSingleton(){
        static AssImporter instance;
        return &instance;
    }

    void Import(const char * path){

        Assimp::Importer importer;
        ResDB* res = ResDB::getSingleton();
        const aiScene* sc = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
        if(!sc)
        {
            cout << importer.GetErrorString() << endl;
            return;
        }
        if(sc->HasTextures()){
            cout << "SCENE HAS TExtURES" << endl;
            for(int i = 0; i < sc->mNumTextures; ++i){
                cout << "TNAME: " << sc->mTextures[i]->mFilename.C_Str() << endl;
            }
        }
        res->prefabs.push_back(ImportObject(sc->mRootNode, sc));

    }
};
#endif // ASSIMPORTER_H
