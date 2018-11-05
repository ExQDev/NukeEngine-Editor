#pragma once
#ifndef NUKEE_TRANSFORM_H
#define NUKEE_TRANSFORM_H
#include "Component.h"
#include "Vector.h"

class Transform : public Component
{
public:
	Vector3 position;
    Vector3 rotation;
    Vector3 scale = {1,1,1};
    GameObject *go = nullptr;

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
        return direction();
    }

    Vector3 right()
    {
        return Vector3{cos(rotation.y - M_PI_2),
                    0,
                    sin(rotation.y - M_PI_2)} * -1.0;
    }

    Vector3 up()
    {
        auto r = right(),
                d = direction();
        auto u = glm::cross( glm::vec3{ r.x, r.y, r.z }, { d.x, d.y, d.z} );
        return { u.x, u.y, u.z};
    }

    Vector3 direction(){
        return Vector3(cos(rotation.y) * cos(rotation.x),
                       sin(rotation.x),
                       cos(rotation.x) * sin(rotation.y));
    }


    Vector3 globalPosition();
    Vector3 globalRotation();
    Vector3 globalScale();

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
        rotation = { 0,0,0 };
		scale = Vector3::one;
	}
};

#endif // !NUKEE_TRANSFORM_H
