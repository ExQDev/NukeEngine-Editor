#pragma once
#ifndef NUKEE_COMPONENT_H
#define NUKEE_COMPONENT_H
//#include <boolinq\include\boolinq\boolinq.h>

class GameObject;
class Transform;
class Script;
class Camera;
class Light;


class Component
{
public:
	bool enabled;
	Transform* transform;
	GameObject* gameobject;
	virtual void Init(GameObject* parent) = 0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Pause() = 0;
	virtual void Reset() = 0;

};
#endif
