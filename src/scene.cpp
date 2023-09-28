#include "scene.hpp"

#include "app.hpp"
#include "object.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <random>

float rnd(float min, float max) {
	return min + (float)std::rand() / ((float)RAND_MAX/(max-min));
}

void Scene::init() {
	objects.clear();
	
	Object* o = new Object(new Mesh(), new Material());
	o->translate(glm::vec3(0.0f, 0.0f, 0.0f));
	objects.push_back(o);
	
	o = new Object(new Mesh(), new Material());
	o->translate(glm::vec3(-1.0f, 5.0f, -8.0f));
	objects.push_back(o);
	
	o = new Object(new Mesh(), new Material());
	o->translate(glm::vec3(3.0f, -4.0f, -6.0f));
	objects.push_back(o);

	o = new Object(new Cube(), new Material());
	o->material->color = glm::vec3(1.0f, 0.0f, 0.0f);
	o->translate(glm::vec3(0.0f, 0.0f, -10.0f));
	o->scale(glm::vec3(1.0f, 2.0f, 1.0f));
	objects.push_back(o);
	
	o = new Object(new Cube(), new Material());
	o->material->color = glm::vec3(0.0f, 0.0f, 1.0f);
	o->translate(glm::vec3(5.0f, 2.0f, -5.0f));
	o->scale(glm::vec3(3.0f, 1.0f, 1.0f));
	objects.push_back(o);
	
	o = new Object(new Cube(), new Material("outline"));
	o->material->color = glm::vec3(1.0f, 0.0f, 1.0f);
	o->translate(glm::vec3(-3.0f, -1.0f, -4.0f));
	o->scale(glm::vec3(0.8f, 0.8f, 0.8f));
	o->rotate(90.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	objects.push_back(o);
	
	o = new Object(new Cube(), new Material("outline"));
	o->material->color = glm::vec3(1.0f, 1.0f, 1.0f);
	o->translate(glm::vec3(0.0f, 10.0f, 0.0f));
	o->scale(glm::vec3(20.0f, 20.0f, 20.0f));
	objects.push_back(o);
	
	o = new Object(new Cube(), new Material("outline"));
	o->material->color = glm::vec3(1.0f, 1.0f, 1.0f);
	o->translate(glm::vec3(9.0f, 10.0f, 9.0f));
	o->scale(glm::vec3(2.0f, 2.0f, 2.0f));
	objects.push_back(o);

	o = new Object(new Cube(), new Material("rainbow"));
	o->material->color = glm::vec3(0.0f, 0.0f, 0.0f);
	o->translate(glm::vec3(9.0f, 12.0f, 9.0f));
	o->scale(glm::vec3(2.0f, 2.0f, 2.0f));
	objects.push_back(o);

	o = new Object(new Quad(), new Material());
	o->material->color = glm::vec3(0.5f, 0.5f, 0.5f);
	o->translate(glm::vec3(0.0f, -8.0f, 0.0f));
	o->scale(glm::vec3(20.0f, 1.0f, -10.0f));
	o->rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	objects.push_back(o);

	for (Object* o : objects) {
		o->init();
	}
}

void Scene::update() {
	objects[5]->rotate(90.0f * app.deltaTime, glm::vec3(1.0f, 1.0f, 1.0f));

	for (Object* o : objects) {
		o->update();
	}
}

void Scene::draw() {
	for (Object* o : objects) {
		o->draw();
	}
}
