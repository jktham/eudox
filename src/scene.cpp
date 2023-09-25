#include "scene.hpp"

#include "app.hpp"
#include "object.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <random>

float Scene::rnd(float min, float max) {
	return min + (float)std::rand() / ((float)RAND_MAX/(max-min));
}

void Scene::init() {
	objects.clear();
	
	Object* object = new Object();
	object->model = glm::translate(object->model, glm::vec3(0.0f, 0.0f, 0.0f));
	objects.push_back(object);
	
	object = new Object();
	object->model = glm::translate(object->model, glm::vec3(-1.0f, 5.0f, -8.0f));
	objects.push_back(object);
	
	object = new Object();
	object->model = glm::translate(object->model, glm::vec3(3.0f, -4.0f, -6.0f));
	objects.push_back(object);

	Cube* cube = new Cube();
	cube->model = glm::translate(cube->model, glm::vec3(0.0f, 0.0f, -10.0f));
	cube->model = glm::scale(cube->model, glm::vec3(1.0f, 2.0f, 1.0f));
	cube->color = glm::vec3(1.0f, 0.0f, 0.0f);
	objects.push_back(cube);
	
	cube = new Cube();
	cube->model = glm::translate(cube->model, glm::vec3(5.0f, 2.0f, -5.0f));
	cube->model = glm::scale(cube->model, glm::vec3(3.0f, 1.0f, 1.0f));
	cube->color = glm::vec3(0.0f, 0.0f, 1.0f);
	objects.push_back(cube);
	
	cube = new Cube();
	cube->shaderName = "outline";
	cube->model = glm::translate(cube->model, glm::vec3(-3.0f, -1.0f, -4.0f));
	cube->model = glm::scale(cube->model, glm::vec3(0.8f, 0.8f, 0.8f));
	cube->model = glm::rotate(cube->model, 3.14f/2.0f, glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)));
	cube->color = glm::vec3(1.0f, 0.0f, 1.0f);
	objects.push_back(cube);
	
	cube = new Cube();
	cube->shaderName = "outline";
	cube->model = glm::translate(cube->model, glm::vec3(0.0f, 10.0f, 0.0f));
	cube->model = glm::scale(cube->model, glm::vec3(20.0f, 20.0f, 20.0f));
	cube->color = glm::vec3(1.0f, 1.0f, 1.0f);
	objects.push_back(cube);
	
	cube = new Cube();
	cube->shaderName = "outline";
	cube->model = glm::translate(cube->model, glm::vec3(9.0f, 10.0f, 9.0f));
	cube->model = glm::scale(cube->model, glm::vec3(2.0f, 2.0f, 2.0f));
	cube->color = glm::vec3(1.0f, 1.0f, 1.0f);
	objects.push_back(cube);

	cube = new Cube();
	cube->shaderName = "rainbow";
	cube->model = glm::translate(cube->model, glm::vec3(9.0f, 12.0f, 9.0f));
	cube->model = glm::scale(cube->model, glm::vec3(2.0f, 2.0f, 2.0f));
	cube->color = glm::vec3(0.0f, 0.0f, 0.0f);
	objects.push_back(cube);

	Quad* quad = new Quad();
	quad->model = glm::translate(quad->model, glm::vec3(0.0f, -8.0f, 0.0f));
	quad->model = glm::scale(quad->model, glm::vec3(20.0f, 1.0f, -10.0f));
	quad->model = glm::rotate(quad->model, 3.14f/2.0f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
	quad->color = glm::vec3(0.5f, 0.5f, 0.5f);
	objects.push_back(quad);

	for (Object* o : objects) {
		o->init();
	}
}

void Scene::update() {
	objects[5]->model = glm::rotate(objects[5]->model, 1.5f * app.deltaTime, glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)));

	for (Object* o : objects) {
		o->update();
	}
}

void Scene::draw() {
	for (Object* o : objects) {
		o->draw();
	}
}
