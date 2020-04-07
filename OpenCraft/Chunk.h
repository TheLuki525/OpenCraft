#pragma once
#include "Block.h"
class Chunk
{
	Block*** blocks;
public:
	void draw();
	void setBlock(int, int, int, GLubyte);
	GLubyte getBlock(int, int, int);
	Chunk(GLubyte);
	~Chunk();
};

