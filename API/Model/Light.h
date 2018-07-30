#pragma once
#ifndef NUKEE_LIGHT_H
#define NUKEE_LIGHT_H
#include "Include.h"

class Light : public Component 
{
	enum LightType 
	{
		directional,
		point,
		area,
		spot
	};
public:
	float intensity, brightness;
	Color color;
	LightType lightType = LightType::directional;
};
#endif // !NUKEE_LIGHT_H
