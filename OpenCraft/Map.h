#pragma once
#include "Chunk.h"
#include <map>
class Map
{
	std::map<std::pair<int, int>, Chunk*> chunks;
public:
	Map();
	~Map();
	void draw(float, float);
	void addChunk(float, float);
	GLubyte getBlock(float, float, float);
	void setBlock(int, int, int, GLubyte);
};

