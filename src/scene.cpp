#include "scene.hpp"

#include <random>

float Scene::rnd(float min, float max) {
	return min + (float)std::rand() / ((float)RAND_MAX/(max-min));
}

void Scene::init() {
	load(1);
}

void Scene::load(int id) {
	if (id == 1) {
		
	}
}

void Scene::update(float time) {
	
}
