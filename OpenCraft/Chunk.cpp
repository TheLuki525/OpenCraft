#include "stdafx.h"
#include "Chunk.h"
#include <iostream>

void Chunk::draw()
{
	for (int x = 0; x < DRAW_DIST; x++)
		for (int y = 0; y < 50; y++)
			for (int z = 0; z < DRAW_DIST; z++)
				if (blocks[x][y][z].visible)
				{
					glPushMatrix();
					{
						glTranslatef(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
						blocks[x][y][z].draw();
					}
					glPopMatrix();
				}
}

void Chunk::setBlock(int, int, int, GLubyte)
{

}

GLubyte Chunk::getBlock(int x, int y, int z)
{
	return blocks[x][y][z].visible;
}

Chunk::Chunk()
{
	//creating blocks[16][128][16]
	blocks = new Block**[DRAW_DIST];
	for (int x = 0; x < DRAW_DIST; x++)
		blocks[x] = new Block*[50];
	for(int x = 0; x < DRAW_DIST; x++)
		for (int y = 0; y < 50; y++)
			blocks[x][y] = new Block[DRAW_DIST];
}


Chunk::~Chunk()
{
	for (int x = 0; x < DRAW_DIST; x++)
		for (int y = 0; y < 128; y++)
			delete[] blocks[x][y];
	for (int x = 0; x < DRAW_DIST; x++)
		delete[] blocks[x];
	delete[] blocks;
}
