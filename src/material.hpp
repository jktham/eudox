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
	std::string shaderName = "base";
	glm::vec3 color = glm::vec3(1.0f);

	unsigned int compileShader(std::string name);
	void updateUniforms();

	Material();
	Material(std::string shaderName);
};
