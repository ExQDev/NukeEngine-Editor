#pragma once
#ifndef NUKEE_CAMERA_H
#define NUKEE_CAMERA_H
#include "Layers.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"
#include <boost/thread.hpp>
#include <render/irender.h>
#include <render/opengl/nukeogl.h>
#include <boost/bind.hpp>

class Camera : public Component
{
private:
	boost::thread* renderThread;
    int prevX, prevY;
    bool moveKey, crosshair;
    float lx=0.0f,ly=0.0f,lz=0.0f;
    const float g_rotation_speed = M_PI/180*0.2;
    bool invertMouse;
public:
    iRender * renderer = nullptr;
	Texture renderTex;
	int r_width = 640, r_height = 480;
    float fov = 90, _near = 0.3, _far = 10000;
	unsigned long int renderLayers;
    bool freeMode;

	Camera()
	{}

    Camera(iRender *renderer): Component("Camera")
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
        if(((NukeOGL*)renderer) != NukeOGL::getSingleton())
            renderer->init(r_width, r_height);
        else
            cout << "[!] Camera of main renderer" << endl;
	}
	
    Camera(GameObject* parent, iRender *renderer)
	{
		this->renderer = renderer;
		Init(parent);
	}

    void ProcessKeyboard(){
        if(!freeMode)
            return;

        if(KeyBoard::getSingleton()->getKeyPressed('w'))
            transform->position +=  transform->direction();
        if(KeyBoard::getSingleton()->getKeyPressed('a'))
            transform->position += transform->right() * -1;
        if(KeyBoard::getSingleton()->getKeyPressed('s'))
            transform->position += transform->direction() * -1;
        if(KeyBoard::getSingleton()->getKeyPressed('d'))
            transform->position += transform->right();

        //cout << "CAM MOV [ " << transform->position.toStringA() << " ]" << endl;
    }

    void ProcessMouse(int key, int mode, int x, int y){
        prevX = x;
        prevY = y;
        if(key == GLUT_RIGHT_BUTTON)
        {
            if(mode == GLUT_DOWN)
            {
                moveKey = true;
                crosshair = true;
            }
            if(mode == GLUT_UP){
                moveKey = false;
                crosshair = false;
            }
        }
    }

    void ProcessMouseMove(int x, int y){
        if(!freeMode)
            return;

        static bool just_warped = false;

        if(just_warped) {
            just_warped = false;
            return;
        }

        if(moveKey) {
            const double limit = 89.0 * M_PI / 180.0;

//            glutWarpPointer(renderer->width/2, renderer->height/2);

            if(prevX == 0 && prevY == 0)
            {
                prevX = x;
                prevY = y;
            }

            int dx = x - prevX,
                    dy = y - prevY;


            //cout << "CAM ROT [ " << transform->rotation.toStringA() << " ]" << endl;
            prevX = x;
            prevY = y;
            transform->rotation.x += ((invertMouse) ? 1 : -1) * dy * g_rotation_speed;// > 0 ? 0.5 : -0.5;
            transform->rotation.y += dx * g_rotation_speed;// > 0 ? 0.5 : -0.5;
            if(transform->rotation.x < -limit)
                transform->rotation.x = -limit;

            if(transform->rotation.x > limit)
                transform->rotation.x = limit;
            just_warped = true;
        }


        if(crosshair)
            glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
        else
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

    }

	void Init(GameObject* parent)
	{
		transform = &parent->transform;
		if(this->renderer)
			this->renderer->transform = transform;
		parent->components.push_back(this);
        if(((NukeOGL*)renderer) != NukeOGL::getSingleton())
            renderer->init(r_width, r_height);
        else
            cout << "[!] Camera of main renderer" << endl;
        //*KeyBoard::getSingleton() += b::function<void(unsigned char, int, int)>(b::bind(&Camera::ProcessKeyboard, b::ref(*this), _1, _2, _3));
        *Mouse::getSingleton() += b::function<void(int, int, int, int)>(b::bind(&Camera::ProcessMouse, b::ref(*this), _1, _2, _3, _4));
        *Mouse::getSingleton() &= b::function<void(int, int)>(b::bind(&Camera::ProcessMouseMove, b::ref(*this), _1, _2));
	}
	void FixedUpdate() {}
	void Update() {
//		renderer->width = this->r_width;
//		renderer->height = this->r_height;
		renderer->fov = fov;
		renderer->Far = _far;
		renderer->Near = _near;
        renderer->_crosshair = crosshair;
        ProcessKeyboard();
	}
	void Reset() {}
	void Pause() {}
	void Destroy()
	{
        renderer->deinit();
	}
};
#endif // !NUKEE_CAMERA_H
