#pragma once

#include <map>
#include <string>
#include <tuple>
#include <variant>
#include <glm/glm.hpp>
#include <vector>

class Resources {
public:
	std::map<std::string, unsigned int> shaders = {};
	std::map<std::string, unsigned int> textures = {};
	std::map<std::string, std::tuple<unsigned int, unsigned int, int>> meshes = {};
	std::map<std::string, std::map<std::string, std::variant<bool, int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4, std::vector<float>, std::vector<glm::vec3>, std::vector<glm::vec4>>>> uniforms = {};

	void clear();
};
