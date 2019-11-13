#pragma once
#include "Chunk.h"
#include <vector>
class Map
{
	Chunk* chunks;
public:
	Map();
	~Map();
	void draw();
	GLubyte getBlock(float, float, float);
	void setBlock(int, int, int, GLubyte);
};

