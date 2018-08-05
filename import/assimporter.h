#ifndef ASSIMPORTER_H
#define ASSIMPORTER_H
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <API/Model/resdb.h>


using namespace std;

class AssImporter
{
    AssImporter() {}
    ~AssImporter() {}
public:
    static AssImporter* getSingleton(){
        static AssImporter instance;
        return &instance;
    }

    void Import(const char * path){

        Assimp::Importer importer;
        ResDB* res = ResDB::getSingleton();
        const aiScene* sc = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
        for(int i = 0; i < sc->mNumMeshes; i++){
            auto cmesh = sc->mMeshes[i];
            Mesh* m = new Mesh();
            m->ImportAIMesh(cmesh);
            res->meshes.push_back(m);
        }
    }
};
#endif // ASSIMPORTER_H
