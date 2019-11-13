#pragma once
#include "vec3.h"
struct Player
{
	vec3 pos, ang, head_ang, speed;
	float phase;
	bool on_ground, phase_dir, flashLight;
	const float max_neck_angle = 40;
	GLuint texHead, texTorso, texHandL, texHandR, texLegL, texLegR;

	Player();
	void walk(bool FWD, bool BWD, bool LFT, bool RGT, bool RUN);
	void draw(bool cam_mode);
};