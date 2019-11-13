#pragma once
#include "vec3.h"
struct Camera
{
	vec3 pos, vertical, lookat;
	float dist, expected_dist;
	bool mode;

	void set(vec3, vec3);

	Camera();
};