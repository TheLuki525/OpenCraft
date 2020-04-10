#include "stdafx.h"
#include "Map.h"
#include "Vec3.h"

Map::Map()
{
	for (int x = -10; x <= 10; x++)
	{
		if (x == 0)
			continue;
		for (int z = -10; z <= 10; z++)
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

std::pair<int, int> chunkToPos(std::pair<int, int> chunk_key)
{
	int chunk_x = chunk_key.first * 16;
	int chunk_z = chunk_key.second * 16;

	if (chunk_key.first > 0)
		chunk_x-=8;
	else
		chunk_x+=8;

	if (chunk_key.second > 0)
		chunk_z -= 8;
	else
		chunk_z += 8;
	return std::pair<int, int>(chunk_x, chunk_z);
}

std::pair<vec3, vec3> Map::apply_ray_scan(vec3 start_pos, vec3 step_vec)//fisrst is the block the player is looking at, second is block before
{
	std::pair<vec3, vec3> ret;
	ret.first = start_pos;
	for (int i = 0; i < 5 * 80; i++)//range of ray is 5 blocks
	{
		ret.second = ret.first;
		ret.first += step_vec;
		if (getBlock(ret.first.x, ret.first.y, ret.first.z))
			return ret;
	}
	return std::pair<vec3, vec3>();
}

void Map::draw(float player_x, float player_z)
{
	auto it = chunks.find(posToChunk(player_x, player_z));
	if (it == chunks.end())//chunk doesn't exist
		return;
	std::pair<int, int> central_chunk_key = it->first;
	std::pair<int, int> central_chunk_pos = chunkToPos(central_chunk_key);
	for (int ix = -4; ix <= 4; ix++)
		for (int iz = -4; iz <= 4; iz++)
		{
			std::pair<int, int> current_chunk_key(central_chunk_key.first + ix, central_chunk_key.second + iz);
			std::pair<int, int> current_chunk_pos = chunkToPos(current_chunk_key);
			if ((current_chunk_pos.first - central_chunk_pos.first) *
				(current_chunk_pos.first - central_chunk_pos.first) +
				(current_chunk_pos.second - central_chunk_pos.second) *
				(current_chunk_pos.second - central_chunk_pos.second) > 16*16*10)
				continue;
			
			auto current_chunk_it = chunks.find(current_chunk_key);
			current_chunk_pos.first -= 8;
			current_chunk_pos.second -= 8;
			if (current_chunk_it != chunks.end())//chunk doesn't exist
			{
				glPushMatrix();
				{
					glTranslatef(current_chunk_pos.first, 0.0f, current_chunk_pos.second);
					current_chunk_it->second->draw();
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
		//it->second->setBlock(ix, iy, iz, rand() % 0xFE + 1);
		return it->second->getBlock(ix, iy, iz);
	}
	return 0;
}

void Map::setBlock(float x, float y, float z, GLubyte id)
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
		it->second->setBlock(ix, iy, iz, id);
	}
}
