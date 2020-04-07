#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	for (int x = -3; x <= 3; x++)
	{
		if (x == 0)
			continue;
		for (int z = -3; z <= 3; z++)
		{
			if (z == 0)
				continue;
			chunks[std::pair<int, int>(x, z)] = new Chunk;
		}
	}
}


Map::~Map()
{
	for (auto &chunk : chunks)
	{
		delete chunk.second;
	}
}

void Map::draw()
{
	for (auto& chunk : chunks)
	{
		int chunk_x = chunk.first.first * 16;
		int chunk_z = chunk.first.second * 16;

		if (chunk_x < 0)
			chunk_x += 8;
		else
			chunk_x -= 8;

		if (chunk_z < 0)
			chunk_z += 8;
		else
			chunk_z -= 8;

		glPushMatrix();
		{
			glTranslatef(chunk_x, 0.0f, chunk_z);
			chunk.second->draw();
		}
		glPopMatrix();
	}
}

GLubyte Map::getBlock(float x, float y, float z)
{
	int ix = static_cast<int>(x), iy = static_cast<int>(y), iz = static_cast<int>(z);
	int chunk_x = ix / 16;
	int chunk_z = iz / 16;

	if (x < 0.0f)
		chunk_x--;
	else
		chunk_x++;

	if (z < 0.0f)
		chunk_z--;
	else
		chunk_z++;

	auto it = chunks.find(std::pair<int, int>(chunk_x, chunk_z));

	if(it != chunks.end())
		return it->second->getBlock(abs(ix)%16, iy, abs(iz)%16);
	return 0;
}

void Map::setBlock(int, int, int, GLubyte)
{
}
