#pragma once

#include <vector>

class Scene {
public:
	float rnd(float min, float max);

	void init();
	void load(int id);
	void update(float time);
};
