#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	chunks = new Chunk;
}


Map::~Map()
{
	delete chunks;
}

void Map::draw()
{
	chunks->draw();
}

GLubyte Map::getBlock(float x, float y, float z)
{
	int ix = static_cast<int>(x), iy = static_cast<int>(y), iz = static_cast<int>(z);
	if (ix < 0 || iy < 0 || iz < 0 || iy > 49 || ix >= DRAW_DIST || iz >= DRAW_DIST)
		return 0;
	return chunks->getBlock(ix, iy, iz);
}

void Map::setBlock(int, int, int, GLubyte)
{
}
