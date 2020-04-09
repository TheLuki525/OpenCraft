#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	for (int x = -1; x <= 1; x++)
	{
		if (x == 0)
			continue;
		for (int z = -1; z <= 1; z++)
		{
			if (z == 0)
				continue;
			chunks[std::pair<int, int>(x, z)] = new Chunk(rand() % 0xFE + 1);
		}
	}
}

Map::~Map()
{
	for (auto& chunk : chunks)
	{
		delete chunk.second;
	}
}

std::pair<int, int> posToChunk(float x, float z)
{
	int chunk_x = static_cast<int>(x) / 16;
	int chunk_z = static_cast<int>(z) / 16;

	if (x < 0.0f)
		chunk_x--;
	else
		chunk_x++;

	if (z < 0.0f)
		chunk_z--;
	else
		chunk_z++;
	return std::pair<int, int>(chunk_x, chunk_z);
}

void Map::draw(float player_x, float player_z)
{
	for (int ix = -1; ix <= 1; ix++)
		for (int iz = -1; iz <= 1; iz++)
		{
			float x = player_x + ix * 16;
			float z = player_z + iz * 16;
			auto it = chunks.find(posToChunk(x, z));
			if (it != chunks.end())//chunk exists
			{
				int chunk_x = it->first.first * 16;
				int chunk_z = it->first.second * 16;
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
					it->second->draw();
				}
				glPopMatrix();
			}
		}
}

void Map::addChunk(float x, float z)
{
	auto it = chunks.find(posToChunk(x, z));
	if (it != chunks.end())//this chunk alredy exists
		return;
	chunks[posToChunk(x, z)] = new Chunk(rand() % 0xFE + 1);
}

GLubyte Map::getBlock(float x, float y, float z)
{
	int ix = static_cast<int>(x), iy = static_cast<int>(y), iz = static_cast<int>(z);
	

	auto it = chunks.find(posToChunk(x, z));

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
		it->second->setBlock(ix, iy, iz, rand() % 0xFE + 1);
		return it->second->getBlock(ix, iy, iz);
	}
	return 0;
}

void Map::setBlock(int ix, int iy, int iz, GLubyte)
{

}
