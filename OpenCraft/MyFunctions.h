#pragma once
#include "vec3.h"
void glTranslatef(vec3 dir);

struct Light
{
	float l_amb[4];
	float l_dif[4];
	float l_spe[4];
	float l_pos[4];
};

GLuint LoadTexture(char * file, int magFilter, int minFilter);
