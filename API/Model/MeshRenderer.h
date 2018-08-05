#pragma once
#ifndef NUKEE_MESHRENDERER_H
#define NUKEE_MESHRENDERER_H
#include "Include.h"

class MeshRenderer : public Component 
{
public:
	Mesh * mesh;

    MeshRenderer() : Component("MeshRenderer"){}

    void Init(GameObject* parent){
        parent->components.push_back(this);
    }

    void Destroy(){

    }

    void Update(){
        if(enabled)
            mesh->Render();
    }

    void FixedUpdate() {}

    void Pause() {}

    void Reset() {
        mesh = nullptr;
    }
};
#endif // !NUKEE_MESHRENDERER_h
