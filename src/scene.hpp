#pragma once

#include "object.hpp"

#include <glm/glm.hpp>
#include <vector>

class Scene {
public:
	std::vector<Object*> objects;

	void init();
	void update();
	void draw();
};
