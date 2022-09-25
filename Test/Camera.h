#pragma once

#include "Math.h"

class Camera
{
	Camera()
		: position_()
	{ }
	Camera(const vec3f& position)
		: position_(position)
	{ }



private:
	vec3f position_;
};