#pragma once

#include "object.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <string>

class Object;

class Material {
public:
	Object* parent;
	unsigned int shader;
	glm::vec3 color = glm::vec3(1.0f);

	float u[32] = {};
	
	std::vector<unsigned int> textures = {};

	void updateUniforms();
	unsigned int compileShader(std::string path);
	unsigned int loadTexture(std::string path);

	Material();
	Material(std::string shaderPath);
	Material(std::string shaderPath, std::string texturePath);
};
