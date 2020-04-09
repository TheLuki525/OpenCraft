#include "stdafx.h"
#include "Chunk.h"
#include <iostream>

void Chunk::draw()
{
	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 128; y++)
			for (int z = 0; z < 16; z++)
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

void Chunk::setBlock(int x, int y, int z, GLubyte id)
{
	if (id != 0)
	{
		//blocks[x][y][z].visible = true;
		//blocks[x][y][z].id = id;
		int i = 0;
		for (float f : { (id & 0b11100000) / 224.0f, (id & 0b00011100) / 28.0f, (id & 0b00000111) / 7.0f, 0.0f })
			blocks[x][y][z].color[i++] = f;
	}
	else
	{
		blocks[x][y][z].visible = false;
		//TO DO: set neighbour blocks visibility (also in neighbour chunks!)
	}
}

GLubyte Chunk::getBlock(int x, int y, int z)
{
	return blocks[x][y][z].id;
}

Chunk::Chunk(GLubyte b)
{
	//creating blocks[16][128][16]
	blocks = new Block**[16];
	for (int x = 0; x < 16; x++)
		blocks[x] = new Block*[128];
	for(int x = 0; x < 16; x++)
		for (int y = 0; y < 128; y++)
			blocks[x][y] = new Block[16]{ b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b};

	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 128; y++)
			for (int z = 0; z < 16; z++)
			{
				if (y < 50)
				{
					blocks[x][y][z].id = 1;
				}
				else
				{
					blocks[x][y][z].id = 0;
				}
			}
	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 128; y++)
			for (int z = 0; z < 16; z++)
			{
				if (x + 1 < 16 && blocks[x + 1][y][z].id == 0)
					blocks[x][y][z].visible = true;
				if (y + 1 < 128 && blocks[x][y + 1][z].id == 0)
					blocks[x][y][z].visible = true;
				if (z + 1 < 16 && blocks[x][y][z + 1].id == 0)
					blocks[x][y][z].visible = true;
				
				/*if (x - 1 >= 0 && blocks[x - 1][y][z].id == 0)
					blocks[x][y][z].visible = true;
				if (y - 1 >= 0 && blocks[x][y - 1][z].id == 0)
					blocks[x][y][z].visible = true;
				if (z - 1 >= 0 && blocks[x][y][z - 1].id == 0)
					blocks[x][y][z].visible = true;*/
			}
}


Chunk::~Chunk()
{
	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 128; y++)
			delete[] blocks[x][y];
	for (int x = 0; x < 16; x++)
		delete[] blocks[x];
	delete[] blocks;
}
