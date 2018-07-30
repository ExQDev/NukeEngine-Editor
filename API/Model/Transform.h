#pragma once
#ifndef NUKEE_TRANSFORM_H
#define NUKEE_TRANSFORM_H
#include "Component.h"
#include "Vector.h"

class Transform : public Component
{
public:
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;
	GameObject *go;

	Transform(GameObject* parent) 
	{
		Init(parent);
	}

	void Init(GameObject* parent) 
	{
		go = parent;
	}

	Vector3 forward() 
	{
		glm::vec3 fwd = glm::rotate(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z), glm::vec3(Vector3::forward.x, Vector3::forward.y, Vector3::forward.z));
		return Vector3(fwd.x, fwd.y, fwd.z);
	}

	void Destroy() 
	{
	
	}

	void Update() 
	{
	
	}

	void FixedUpdate() 
	{
	
	}

	void Pause() 
	{
	
	}

	void Reset() 
	{
		position = Vector3::zero;
		rotation = { 0,0,0,0 };
		scale = Vector3::one;
	}
};

#endif // !NUKEE_TRANSFORM_H
