#include "stdafx.h"
#include "Map.h"


Map::Map()
	:chunks_quarters(4)
{
	for (auto &quarter : chunks_quarters)
	{
		for (int i = 0; i < 3; i++)
		{
			quarter.push_back(std::vector<Chunk>());
			for (int j = 0; j < 3; j++)
				quarter[i].push_back(Chunk());
		}
	}
}


Map::~Map()
{
}

void Map::draw()
{
	for (auto& quarter : chunks_quarters)
		for (auto& quarter_line : quarter)
			for (auto& chunk : quarter_line)
				chunk.draw();
}

GLubyte Map::getBlock(float x, float y, float z)
{
	int ix = static_cast<int>(x), iy = static_cast<int>(y), iz = static_cast<int>(z);
	if (iy < 0 || iy > 127 || abs(ix) >= DRAW_DIST || abs(iz) >= DRAW_DIST)
		return 0;
	int quarter = 0;
	if (ix >= 0)
	{
		if (iz >= 0)
		{
			quarter = 0;
		}
		else
		{
			quarter = 3;
		}
	}
	else
	{
		if (iz >= 0)
		{
			quarter = 1;
		}
		else
		{
			quarter = 2;
		}
	}
	return chunks_quarters[quarter][ix/4][iy/4].getBlock(ix%16, iy, iz%16);
}

void Map::setBlock(int, int, int, GLubyte)
{
}
