#pragma once
#ifndef NUKEE_MATERIAL_H
#define NUKEE_MATERIAL_H
#include <iostream>
#include "Texture.h"
#include "Shader.h"
#include <assimp/material.h>

using namespace std;

class Material 
{
public:
    char* name;
    Texture* diff;
    Texture* norm;
    Texture* spec;

    Shader* shader;
    aiMaterial* aiMat;

    void ImportAiMaterial(aiMaterial * m){
        aiString diffName;
        m->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &diffName);
        cout << "DIFF_NAME: " << diffName.C_Str() << endl;
        aiMat = m;
    }
};
#endif // !NUKEE_MATERIAL_H
