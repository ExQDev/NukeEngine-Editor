#ifndef RAY_H
#define RAY_H
#include "Vector.h"
#include "Collider.h"
#include <glm/glm.hpp>

struct Ray
{
    Vector3 start;
    Vector3 direction;
    double length;
    int w, h;

    Ray() {}
    bool Collide(Collider collider){
        glm::vec4 viewport = glm::vec4(0, 0, w, h);
        glm::vec3 wincoord = glm::vec3(start.x, start.y, start.z);
//        glm::vec3 objcoord = glm::unProject(wincoord, view, projection, viewport);
        return false;
    }
};

#endif // RAY_H
