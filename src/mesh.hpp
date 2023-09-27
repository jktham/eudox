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
	int stride = 11;

	void generateBuffers();
	void updateBuffers();
	virtual std::vector<float> getVertices();
};

class Cube : public Mesh {
public:
	std::vector<float> getVertices();
};

class Quad : public Mesh {
public:
	std::vector<float> getVertices();
};
