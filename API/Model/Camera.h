#pragma once
#ifndef NUKEE_CAMERA_H
#define NUKEE_CAMERA_H
#include "Layers.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"
#include <boost/thread.hpp>
#include <render/irender.h>

class Camera : public Component
{
private:
	boost::thread* renderThread;

	
public:
    iRender * renderer = nullptr;
	Texture renderTex;
	int r_width = 640, r_height = 480;
	float fov, _near, _far;
	unsigned long int renderLayers;
	
	Camera()
	{}

    Camera(iRender *renderer)
	{
		this->renderer = renderer;
		this->renderer->transform = transform;
        renderLayers = NUKEE_LAYER_DEFAULT | NUKEE_LAYER_SKY | NUKEE_LAYER_WATER;
#ifdef EDITOR
        renderLayers |= NUKEE_LAYER_EDITOR;
#endif // EDITOR
		renderer->width = this->r_width;
		renderer->height = this->r_height;
		renderer->fov = fov;
		renderer->Far = _far;
		renderer->Near = _near;
        renderer->init(r_width, r_height);

	}
	
    Camera(GameObject* parent, iRender *renderer)
	{
		this->renderer = renderer;
		Init(parent);
	}

	void Init(GameObject* parent)
	{
		transform = &parent->transform;
		if(this->renderer)
			this->renderer->transform = transform;
		parent->components.push_back(this);
        this->renderer->init(r_width, r_height);
	}
	void FixedUpdate() {}
	void Update() {
		renderer->width = this->r_width;
		renderer->height = this->r_height;
		renderer->fov = fov;
		renderer->Far = _far;
		renderer->Near = _near;
	}
	void Reset() {}
	void Pause() {}
	void Destroy()
	{
        renderer->deinit();
	}
};
#endif // !NUKEE_CAMERA_H
