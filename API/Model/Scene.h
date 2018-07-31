#pragma once
#ifndef NUKEE_SCENE_H
#define NUKEE_SCENE_H
#include "GameObject.h"

class Scene
{
public:
	std::string name = "Default scene";
    bc::list<GameObject*> hierarchy;

	GameObject* Get(std::string name) 
	{
		for (auto go : hierarchy)
			if (go->name == name)
				return go;
		return nullptr;
	}

	void Add(GameObject* go) 
	{
		hierarchy.push_back(go);
	}

	void Start() 
	{
		
	}

	void Update() 
	{
		for (GameObject* go : hierarchy) 
		{
			go->Update();
		}
	}
};

#endif // !NUKEE_SCENE_H
