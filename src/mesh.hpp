#pragma once

#include "object.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <string>

class Object;

class Mesh {
public:
	Object* parent;
	unsigned int vao;
	unsigned int vbo;
	std::vector<float> vertices = {};
	int stride = 1;

	virtual void generateBuffers();
	virtual void updateBuffers();
	Mesh();
	Mesh(std::vector<float> verts);
};

class ScreenQuad : public Mesh {
public:
	void generateBuffers();
	void updateBuffers();
	ScreenQuad();
};
