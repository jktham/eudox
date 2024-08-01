#pragma once

#include "object.hpp"

#include <glm/glm.hpp>
#include <string>
#include <map>
#include <variant>

class Object;

class Material {
public:
	Object* parent;
	unsigned int shader;

	float u[32] = {};
	unsigned int textures[32] = {};
	std::map<std::string, std::variant<int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4>> uniforms;

	void updateUniforms();
	unsigned int compileShader(std::string path);
	unsigned int loadTexture(std::string path);
	void getUniforms(std::string source);

	Material();
	Material(std::string shaderPath);
	Material(std::string shaderPath, std::string texturePath);
};
