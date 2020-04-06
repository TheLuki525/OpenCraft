#pragma once
#include "Chunk.h"
#include <vector>
class Map
{
	std::vector<std::vector<std::vector<Chunk>>> chunks_quarters;
public:
	Map();
	~Map();
	void draw();
	GLubyte getBlock(float, float, float);
	void setBlock(int, int, int, GLubyte);
};

