#pragma once
class Block
{
public:
	GLubyte id;
	bool visible;
	void draw();
	Block();
	~Block();
};

