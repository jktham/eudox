#pragma once

#include "object.hpp"

#include <glm/glm.hpp>
#include <vector>

class Scene {
public:
	int id = 0;
	std::vector<Object*> objects;
	Object* postProcessing;

	void init();
	void update();
	void draw();
};