#pragma once

#include "Math.h"

class Camera
{
public:
	Camera()
		: position_()
	{ }
	Camera(const vec3f& position)
		: position_(position)
	{ }

	const vec3f& GetPos() const
	{
		return position_;
	}

	float GetZNear() const
	{
		return zNear_;
	}

	float GetZFar() const
	{
		return zFar_;
	}

	float GetFov() const
	{
		return fov_;
	}

	float GetAspect() const
	{
		return aspect_;
	}


private:
	vec3f position_;
	float zNear_;
	float zFar_;
	float fov_;
	float aspect_;
};