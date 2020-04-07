#pragma once
class Block
{
public:
	GLubyte id;
	bool visible;
	float color[4];
	void draw();
	Block(GLubyte id);
	~Block();
};

