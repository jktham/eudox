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

	virtual void generateBuffers();
	virtual void updateBuffers();
	std::vector<float> loadModel(std::string path);
	
	Mesh();
	Mesh(std::vector<float> verts);
	Mesh(std::string modelPath);
};
