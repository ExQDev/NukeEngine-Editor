#pragma once
#ifndef NUKEE_GAMEOBJECT_H
#define NUKEE_GAMEOBJECT_H
#include <boost/container/list.hpp>
namespace bc = boost::container;

#include "Transform.h"
#include "Layers.h"
#include "ID.h"

class GameObject : public Component
{
public:
	Transform transform = { this };
	GameObject* parent;
	ID id;
	std::string name = "GameObject";
	std::string tag = "Untagged";
	int layer = Layer::L_DEFAULT;

    bc::list<Component*> components;
    bc::list<GameObject*> children;

	GameObject(std::string name) 
	{
		this->name = name;
		this->gameobject = this;
		this->transform = transform;
	}
	~GameObject() {}


	template<class T>
	T* GetComponent()
	{
		for(auto cmp : components)
			if (auto res = dynamic_cast<T*>(cmp))
				return res;
		return nullptr;
	}
	
	
	template<class T>
    bc::list<T*> GetComponents()
	{
        bc::list<T*> lst;
        for(auto cmp : lst)
			if (auto res = dynamic_cast<T*>(cmp))
				lst.push_back(res);
		return lst;
	}

	void Init(GameObject* parent) 
	{
		this->parent = parent;
	}
	void FixedUpdate() {}
	void Update() 
	{
		for (auto child : children) 
			child->Update();
		for (auto cmp : components)
			cmp->Update();
	}

    void SetParent(GameObject* newparent){
        newparent->children.push_back(this);
        parent = newparent;
    }

    void AddChild(GameObject* newChild){
        children.push_back(newChild);
        newChild->parent = this;
    }

	void Reset() {}
	void Pause() {}
	void Destroy() 
	{
		for (auto x : children)
		{
			x->Destroy();
		}
        parent->gameobject->children.remove(this);
        delete this;
	}

private:

};
#endif // !NUKEE_GAMEOBJECT_H
