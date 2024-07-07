#pragma once

#include <map>
#include <string>
#include <tuple>

class Resources {
public:
	std::map<std::string, unsigned int> shaders = {};
	std::map<std::string, unsigned int> textures = {};
	std::map<std::string, std::tuple<unsigned int, unsigned int, int>> meshes = {};

	void clear();
};
