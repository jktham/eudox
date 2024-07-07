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
	int triangles = 0;

	virtual void generateBuffers();
	virtual void updateBuffers(std::vector<float> vertices);
	std::vector<float> loadModel(std::string path);
	
	Mesh();
	Mesh(std::vector<float> vertices);
	Mesh(std::string modelPath);
};
