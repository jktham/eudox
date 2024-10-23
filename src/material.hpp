#pragma once

#include "object.hpp"

#include <glm/glm.hpp>
#include <string>
#include <map>
#include <variant>
#include <vector>

class Object;

class Material {
public:
	Object* parent;
	unsigned int shader;

	float u[32] = {};
	unsigned int textures[32] = {};
	std::map<std::string, std::variant<bool, int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4, std::vector<float>, std::vector<glm::vec3>, std::vector<glm::vec4>>> uniforms;

	void updateUniforms();
	unsigned int compileShader(std::string path);
	unsigned int loadTexture(std::string path, bool noInterp = false);
	void getUniforms(std::string source);

	Material();
	Material(std::string shaderPath);
	Material(std::string shaderPath, std::string texturePath);
};
