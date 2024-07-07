#pragma once

#include "object.hpp"

#include <glm/glm.hpp>
#include <vector>

class Scene {
public:
	int sceneId = 1;
	int postId = 1;

	std::vector<Object*> worldObjects;
	std::vector<Object*> uiObjects;
	Object* postProcessing;

	void init();
	void update();
	void draw();
};