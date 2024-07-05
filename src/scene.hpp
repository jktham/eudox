#pragma once

#include "object.hpp"

#include <glm/glm.hpp>
#include <vector>

class Scene {
public:
	int id = 0;
	std::vector<Object*> worldObjects;
	std::vector<Object*> uiObjects;
	Object* postProcessing;

	void init();
	void update();
	void draw();
};