#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	for (int x = -2; x <= 2; x++)
	{
		if (x == 0)
			continue;
		for (int z = -2; z <= 2; z++)
		{
			if (z == 0)
				continue;
			chunks[std::pair<int, int>(x, z)] = new Chunk(rand() % 0xFE + 1);
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
		int shift = 8;
		if (chunk_x < 0)
			chunk_x += shift;
		else
			chunk_x -= shift;

		if (chunk_z < 0)
			chunk_z += shift;
		else
			chunk_z -= shift;
		chunk_x -= shift;
		chunk_z -= shift;

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

	if (it != chunks.end())
	{
		if (x < 0)
			ix = 15 + (ix % 16);
		else
			ix = ix % 16;

		if (z < 0)
			iz = 15 + (iz % 16);
		else
			iz = iz % 16;
		it->second->setBlock(ix, iy, iz, rand()%0xFE+1);
		return it->second->getBlock(ix, iy, iz);
	}
	return 0;
}

void Map::setBlock(int ix, int iy, int iz, GLubyte)
{

}
