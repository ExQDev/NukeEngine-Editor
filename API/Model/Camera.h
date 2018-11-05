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

public:
    bool invertMouse = false;
    iRender * renderer = nullptr;
	Texture renderTex;
	int r_width = 640, r_height = 480;
    float fov = 90, _near = 0.3, _far = 10000;
	unsigned long int renderLayers;
    bool freeMode;

    Camera() : Component("Camera")
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
	
    Camera(GameObject* parent, iRender *renderer) : Component("Camera")
	{
		this->renderer = renderer;
		Init(parent);
	}

    Vector3 ScreenPosToWorldRay(
            int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
            int screenWidth, int screenHeight,  // Window size, in pixels
            glm::mat4 ViewMatrix,               // Camera position and orientation
            glm::mat4 ProjectionMatrix         // Camera parameters (ratio, field of view, near and far planes)
            , glm::vec3 &out_origin
){

    // The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
    glm::vec4 RayStart_NDC(
                  (2.0f * mouseX)/screenWidth - 1.0f, // [0,1024] -> [-1,1]
                  1.0f - (2.0f * mouseY)/screenHeight, // [0, 768] -> [-1,1]
                  -1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
                  1.0f
                  );
    glm::vec4 RayEnd_NDC(
                (2.0f * mouseX)/screenWidth - 1.0f,
                1.0f - (2.0f * mouseY)/screenHeight,
                0.0,
                1.0f
                );


    // The Projection matrix goes from Camera Space to NDC.
    // So inverse(ProjectionMatrix) goes from NDC to Camera Space.
    glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);

    // The View Matrix goes from World Space to Camera Space.
    // So inverse(ViewMatrix) goes from Camera Space to World Space.
    glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);

    glm::vec4 RayStart_camera = InverseProjectionMatrix * RayStart_NDC;
    RayStart_camera/=RayStart_camera.w;
    glm::vec4 RayStart_world  = InverseViewMatrix       * RayStart_camera;
    RayStart_world /=RayStart_world.w;
    glm::vec4 RayEnd_camera   = InverseProjectionMatrix * RayEnd_NDC;
    RayEnd_camera  /=RayEnd_camera.w;
    glm::vec4 RayEnd_world    = InverseViewMatrix       * RayEnd_camera;
    RayEnd_world   /=RayEnd_world.w;


    // Faster way (just one inverse)
    //glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
    //glm::vec4 RayStart_world = M * RayStart_NDC; RayStart_world/=RayStart_world.w;
    //glm::vec4 RayEnd_world   = M * RayEnd_NDC  ; RayEnd_world  /=RayEnd_world.w;


    glm::vec3 RayDir_world(RayEnd_world - RayStart_world);
    RayDir_world = glm::normalize(RayDir_world);


    out_origin = glm::vec3(RayStart_world);
    auto out = glm::normalize(RayDir_world);
    return {out.x, out.y, out.z};
}

    bool  RayOBBIntersection(
                                glm::vec3 ray_origin,        // Ray origin, in world space
                                glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
                                glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
                                glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
                                glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
                                float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
    ){

        // Intersection method from Real-Time Rendering and Essential Mathematics for Games

        float tMin = 0.0f;
        float tMax = 100000.0f;

        glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

        glm::vec3 delta = OBBposition_worldspace - ray_origin;

        // Test intersection with the 2 planes perpendicular to the OBB's X axis
        {
            glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
            float e = glm::dot(xaxis, delta);
            float f = glm::dot(ray_direction, xaxis);

            if ( fabs(f) > 0.001f ){ // Standard case

                float t1 = (e+aabb_min.x)/f; // Intersection with the "left" plane
                float t2 = (e+aabb_max.x)/f; // Intersection with the "right" plane
                // t1 and t2 now contain distances betwen ray origin and ray-plane intersections

                // We want t1 to represent the nearest intersection,
                // so if it's not the case, invert t1 and t2
                if (t1>t2){
                    float w=t1;t1=t2;t2=w; // swap t1 and t2
                }

                // tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
                if ( t2 < tMax )
                    tMax = t2;
                // tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
                if ( t1 > tMin )
                    tMin = t1;

                // And here's the trick :
                // If "far" is closer than "near", then there is NO intersection.
                // See the images in the tutorials for the visual explanation.
                if (tMax < tMin )
                    return false;

            }else{ // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
                if(-e+aabb_min.x > 0.0f || -e+aabb_max.x < 0.0f)
                    return false;
            }
        }


        // Test intersection with the 2 planes perpendicular to the OBB's Y axis
        // Exactly the same thing than above.
        {
            glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
            float e = glm::dot(yaxis, delta);
            float f = glm::dot(ray_direction, yaxis);

            if ( fabs(f) > 0.001f ){

                float t1 = (e+aabb_min.y)/f;
                float t2 = (e+aabb_max.y)/f;

                if (t1>t2){float w=t1;t1=t2;t2=w;}

                if ( t2 < tMax )
                    tMax = t2;
                if ( t1 > tMin )
                    tMin = t1;
                if (tMin > tMax)
                    return false;

            }else{
                if(-e+aabb_min.y > 0.0f || -e+aabb_max.y < 0.0f)
                    return false;
            }
        }


        // Test intersection with the 2 planes perpendicular to the OBB's Z axis
        // Exactly the same thing than above.
        {
            glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
            float e = glm::dot(zaxis, delta);
            float f = glm::dot(ray_direction, zaxis);

            if ( fabs(f) > 0.001f ){

                float t1 = (e+aabb_min.z)/f;
                float t2 = (e+aabb_max.z)/f;

                if (t1>t2){float w=t1;t1=t2;t2=w;}

                if ( t2 < tMax )
                    tMax = t2;
                if ( t1 > tMin )
                    tMin = t1;
                if (tMin > tMax)
                    return false;

            }else{
                if(-e+aabb_min.z > 0.0f || -e+aabb_max.z < 0.0f)
                    return false;
            }
        }

        intersection_distance = tMin;
        return true;

    }

    void ProcessKeyboard(){
        if(!freeMode)
            return;

        if(KeyBoard::getSingleton()->getKeyPressed('w'))
            transform->position +=  transform->direction() * 3;
        if(KeyBoard::getSingleton()->getKeyPressed('a'))
            transform->position += transform->right() * -3;
        if(KeyBoard::getSingleton()->getKeyPressed('s'))
            transform->position += transform->direction() * -3;
        if(KeyBoard::getSingleton()->getKeyPressed('d'))
            transform->position += transform->right() * 3;

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

    void mouseScroll(int button, int dir, int x, int y){
        transform->position += transform->direction() * dir * 3;
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
        *Mouse::getSingleton() *= b::function<void(int, int, int, int)>(b::bind(&Camera::mouseScroll, b::ref(*this), _1, _2, _3, _4));
	}
	void FixedUpdate() {}
	void Update() {
//		renderer->width = this->r_width;
//		renderer->height = this->r_height;
		renderer->fov = fov;
		renderer->Far = _far;
		renderer->Near = _near;
        renderer->_crosshair = crosshair;
        renderer->update();
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
