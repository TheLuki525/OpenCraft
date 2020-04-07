#include "stdafx.h"
#include "Block.h"


void Block::draw()
{
	if (id == 0)
	{
		visible = false;
		return;
	}
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color);
	glutSolidCube(1.0);
}

Block::Block(GLubyte id)
	:id(id), color{ (id & 0b11100000) / 224.0f, (id & 0b00011100) / 28.0f, (id & 0b00000111) / 7.0f, 0.0f }
{
	visible = false;
}


Block::~Block()
{
}
