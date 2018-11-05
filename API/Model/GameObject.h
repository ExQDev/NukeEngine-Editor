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
    GameObject* parent = nullptr;
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

    void AddComponent(Component* cmp){
        cmp->Init(this);
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

    template <class T>
    void Update(){
        for(auto c : children){
            if(auto mr = c->GetComponent<T>())
                mr->Update();
        }
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

Vector3 Transform::globalPosition(){
//    cout << "GO: " << this->go << endl;
//    cout << "GO PARENT: " << this->go->parent << endl;
//    cout << "GO PARENT POS: " << this->go->parent->transform.position.toStringA() << endl;
    return Vector3((this->go != nullptr && this->go->parent != nullptr)
            ?(this->position + this->go->parent->transform.globalPosition())
           :(this->position));
}

Vector3 Transform::globalRotation(){
    return Vector3((this->go->parent)?(this->rotation + this->go->parent->transform.globalRotation()):(this->rotation));
}

Vector3 Transform::globalScale(){
    return Vector3((this->go->parent)?(this->scale * this->go->parent->transform.globalScale()):(this->scale));
}
#endif // !NUKEE_GAMEOBJECT_H
