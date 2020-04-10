#pragma once
#include "Chunk.h"
#include <map>
#include "Vec3.h"

class Map
{
	std::map<std::pair<int, int>, Chunk*> chunks;
public:
	Map();
	~Map();
	void draw(float, float);
	void addChunk(float, float);
	GLubyte getBlock(float, float, float);
	void setBlock(float, float, float, GLubyte);
	std::pair<vec3, vec3> apply_ray_scan(vec3 start_pos, vec3 step_vec);
};

