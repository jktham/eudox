#pragma once

#include "object.hpp"

#include <glm/glm.hpp>
#include <vector>

class Scene {
public:
	int sceneId = 1;
	int postId = 1;
	float time = 0.0f;
	float deltaTime = 0.0f;
	bool paused = false;

	std::vector<Object*> world;
	std::vector<Object*> ui;
	Object* post;

	void init();
	void initPost();
	void update();
	void draw();
};