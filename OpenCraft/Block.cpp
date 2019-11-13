#include "stdafx.h"
#include "Block.h"


void Block::draw()
{
	float m[] = { (id & 0b11100000)/224.0f, (id & 0b00011100)/28.0f, (id & 0b00000111)/7.0f, 0.0f };
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, m);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m);
	glutSolidCube(1.0);
}

Block::Block()
{

	id = rand() & 0xFF;
	visible = rand() < 1000;
}


Block::~Block()
{
}
