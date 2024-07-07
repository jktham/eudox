#include "scene.hpp"

#include "app.hpp"
#include "object.hpp"
#include "data.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <random>
#include <glad/gl.h>

float rnd(float min, float max) {
	return min + (float)std::rand() / ((float)RAND_MAX/(max-min));
}

void Scene::init() {
	worldObjects.clear();
	uiObjects.clear();
	Object* o;
	
	if (id == 0) {
		postProcessing = new Object(new Mesh(quad), new Material("post/kernel"));
		postProcessing->scale(glm::vec3(app.width, app.height, 1.0f));
		postProcessing->material->textures[0] = app.fbColor;
		postProcessing->material->textures[1] = app.fbDepth;
		postProcessing->material->textures[2] = app.fbPosition;
		postProcessing->material->textures[3] = app.fbNormal;
		std::copy(&edgeKernel[0], &edgeKernel[9], postProcessing->material->u);

		o = new Object(new Mesh(), new Material());
		o->translate(glm::vec3(0.0f, 0.0f, 0.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(triangle), new Material("world/textured", "test.png"));
		o->translate(glm::vec3(-1.0f, 5.0f, -8.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(), new Material());
		o->translate(glm::vec3(3.0f, -4.0f, -6.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh(cube), new Material("world/textured", "test.png"));
		o->material->color = glm::vec3(1.0f, 0.0f, 0.0f);
		o->translate(glm::vec3(0.0f, 0.0f, -10.0f));
		o->scale(glm::vec3(1.0f, 2.0f, 1.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(cube), new Material());
		o->material->color = glm::vec3(0.0f, 0.0f, 1.0f);
		o->translate(glm::vec3(5.0f, 2.0f, -5.0f));
		o->scale(glm::vec3(3.0f, 1.0f, 1.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(cube), new Material("world/outline"));
		o->material->color = glm::vec3(1.0f, 0.0f, 1.0f);
		o->translate(glm::vec3(-3.0f, -1.0f, -4.0f));
		o->scale(glm::vec3(0.8f, 0.8f, 0.8f));
		o->rotate(90.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(cube), new Material("world/outline"));
		o->material->color = glm::vec3(1.0f, 1.0f, 1.0f);
		o->translate(glm::vec3(0.0f, 10.0f, 0.0f));
		o->scale(glm::vec3(20.0f, 20.0f, 20.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(cube), new Material("world/outline"));
		o->material->color = glm::vec3(1.0f, 1.0f, 1.0f);
		o->translate(glm::vec3(9.0f, 10.0f, 9.0f));
		o->scale(glm::vec3(2.0f, 2.0f, 2.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh(cube), new Material("world/rainbow"));
		o->material->color = glm::vec3(0.0f, 0.0f, 0.0f);
		o->material->u[0] = 1.0f;
		o->translate(glm::vec3(9.0f, 12.0f, 9.0f));
		o->scale(glm::vec3(2.0f, 2.0f, 2.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh(quad), new Material());
		o->material->color = glm::vec3(0.9f, 0.9f, 0.1f);
		o->translate(glm::vec3(0.0f, -8.0f, -5.0f));
		o->scale(glm::vec3(20.0f, 1.0f, -10.0f));
		o->rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(cube), new Material("world/shaded"));
		o->material->color = glm::vec3(1.0f, 1.0f, 1.0f);
		o->material->u[0] = 0.1f;
		o->material->u[1] = 0.6f;
		o->material->u[2] = 0.4f;
		o->material->u[3] = 32.0f;
		o->material->u[4] = 0.0f;
		o->material->u[5] = 0.0f;
		o->material->u[6] = 0.0f;
		o->translate(glm::vec3(0.0f, -10.0f, 0.0f));
		o->scale(glm::vec3(4.0f, 4.0f, 4.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("test.obj"), new Material("world/shaded"));
		o->material->u[0] = 0.1f;
		o->material->u[1] = 0.6f;
		o->material->u[2] = 0.4f;
		o->material->u[3] = 32.0f;
		o->translate(glm::vec3(-10.0f, 0.0f, -10.0f));
		o->scale(glm::vec3(4.0f, 4.0f, 4.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh(cube), new Material("ui/textured", "test.png"));
		o->translate(glm::vec3(100.0f, app.height - 200.0f, 0.0f));
		o->scale(glm::vec3(100.0f, 100.0f, 1.0f));
		uiObjects.push_back(o);

		o = new Object(new Mesh(quad), new Material("ui/textured"));
		o->material->textures[0] = app.fbColor;
		o->translate(glm::vec3(10.0f, 10.0f, 0.0f));
		o->scale(glm::vec3(320.0f, 180.0f, 1.0f));
		uiObjects.push_back(o);

		o = new Object(new Mesh(quad), new Material("ui/textured"));
		o->material->textures[0] = app.fbDepth;
		o->translate(glm::vec3(10.0f, 200.0f, 0.0f));
		o->scale(glm::vec3(320.0f, 180.0f, 1.0f));
		uiObjects.push_back(o);

		o = new Object(new Mesh(quad), new Material("ui/textured"));
		o->material->textures[0] = app.fbPosition;
		o->translate(glm::vec3(10.0f, 390.0f, 0.0f));
		o->scale(glm::vec3(320.0f, 180.0f, 1.0f));
		uiObjects.push_back(o);

		o = new Object(new Mesh(quad), new Material("ui/textured"));
		o->material->textures[0] = app.fbNormal;
		o->translate(glm::vec3(10.0f, 580.0f, 0.0f));
		o->scale(glm::vec3(320.0f, 180.0f, 1.0f));
		uiObjects.push_back(o);

	} else if (id == 1) {
		postProcessing = new Object(new Mesh(quad), new Material("post/base"));
		postProcessing->scale(glm::vec3(app.width, app.height, 1.0f));
		postProcessing->material->textures[0] = app.fbColor;
		postProcessing->material->textures[1] = app.fbDepth;
		postProcessing->material->textures[2] = app.fbPosition;
		postProcessing->material->textures[3] = app.fbNormal;

		o = new Object(new Mesh("test2.obj"), new Material("world/shadedtextured", "test.png"));
		o->material->u[0] = 0.1f;
		o->material->u[1] = 0.6f;
		o->material->u[2] = 0.4f;
		o->material->u[3] = 32.0f;
		o->translate(glm::vec3(0.0f, 0.0f, 0.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("test.obj"), new Material("world/noise"));
		o->translate(glm::vec3(5.0f, 0.0f, 0.0f));
		worldObjects.push_back(o);

	}

	for (Object* o : worldObjects) {
		o->init();
	}
	for (Object* o : uiObjects) {
		o->init();
	}
	postProcessing->init();
}

void Scene::update() {
	if (id == 0) {
		glm::vec3 light = glm::vec3(100.0f*cos(app.time*2.0f), 200.0f, 100.0f*sin(app.time*2.0f));
		worldObjects[5]->rotate(90.0f * app.deltaTime, glm::vec3(1.0f, 1.0f, 1.0f));
		worldObjects[10]->material->u[4] = light.x;
		worldObjects[10]->material->u[5] = light.y;
		worldObjects[10]->material->u[6] = light.z;
		worldObjects[11]->material->u[4] = light.x;
		worldObjects[11]->material->u[5] = light.y;
		worldObjects[11]->material->u[6] = light.z;
		uiObjects[0]->rotate(90.0f * app.deltaTime, glm::vec3(1.0f, 1.0f, 1.0f));

	} else if (id == 1) {
		glm::vec3 light = glm::vec3(100.0f*cos(app.time*2.0f), 200.0f, 100.0f*sin(app.time*2.0f));
		worldObjects[0]->material->u[4] = light.x;
		worldObjects[0]->material->u[5] = light.y;
		worldObjects[0]->material->u[6] = light.z;

	}

	for (Object* o : worldObjects) {
		o->update();
	}
	for (Object* o : uiObjects) {
		o->update();
	}
	postProcessing->update();
}

void Scene::draw() {
	glBindFramebuffer(GL_FRAMEBUFFER, app.framebuffer);
	glViewport(0, 0, app.fbWidth, app.fbHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	for (Object* o : worldObjects) {
		o->draw();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, app.width, app.height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	postProcessing->draw();

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	for (Object* o : uiObjects) {
		o->draw();
	}
}
