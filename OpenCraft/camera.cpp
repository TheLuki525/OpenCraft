#include "stdafx.h"
#include "camera.h"

Camera::Camera()
	:vertical(0.0f, 1.0f, 0.0f)
{
	dist = -4.0f;//cam behind player
	expected_dist = dist;
	mode = true;//true - 3rd person cam, false 1st person cam
}

void Camera::set(vec3 lookVec, vec3 player_pos)
{
	if (dist < expected_dist - 0.1f)
		dist += 0.25f;
	else if (dist > expected_dist + 0.1f)
		dist -= 0.25f;
	else
		dist = expected_dist;

	if (dist >= 0.0f)
	{
		mode = false;//1st person
		dist = 0.0f;
		expected_dist = 0.0f;
	}
	else
		mode = true;//3rd person

	if (mode)//3rd person cam
	{
		pos = lookVec*dist + player_pos;
		lookat = player_pos;
	}
	else//1st person cam
	{
		lookat = lookVec * 4.0f + player_pos;
		pos = player_pos;
	}

	pos.y += PLAYER_EYE_HEIGHT;
	gluLookAt(
		pos.x, pos.y, pos.z,//camera position
		lookat.x, lookat.y + PLAYER_EYE_HEIGHT, lookat.z,// camera look-at point
		vertical.x, vertical.y, vertical.z //vertical vector
	);
}
