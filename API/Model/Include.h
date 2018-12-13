#pragma once
#include <cmath>
#include <boost/container/list.hpp>

#ifdef WIN32
#include <Windows.h>
#endif

#include "ID.h"
#include "Vector.h"
#include "Color.h"
class Vector4 Color::toVector4()
{
    return Vector4(r,g,b,a);
}
Vector3 Vector2::toVector3()
{
    return Vector3(x, y, 0);
}

Vector4 Vector2::toVector4()
{
    return Vector4(x, y, 0, 0);
}

Vector4 Vector3::toVector4()
{
    return Vector4(x, y, z, 0);
}

Color Vector4::toColor()
{
    return Color(x, y, z, w);
}

#include "Math.h"

#include "Component.h"

#include "Script.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshRenderer.h"




#include "Clock.h"
#include "Time.h"

#include "Transform.h"
#include "GameObject.h"


#include "Scene.h"
#include "Game.h"
#include "Package.h"
#include "Module.h"

// --------------Already defined troouble-----------------
