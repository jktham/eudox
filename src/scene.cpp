#include "scene.hpp"

#include "app.hpp"
#include "object.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <random>
#include <glad/gl.h>

float rnd(float min, float max) {
	return min + (float)std::rand() / ((float)RAND_MAX/(max-min));
}

float sharpenKernel[9] = {
	-1.0f, -1.0f, -1.0f,
	-1.0f,  9.0f, -1.0f,
	-1.0f, -1.0f, -1.0f
};
float blurKernel[9] = {
	1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f,
	2.0f/16.0f, 4.0f/16.0f, 2.0f/16.0f,
	1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f
};
float edgeKernel[9] = {
	1.0f,  1.0f, 1.0f,
	1.0f, -8.0f, 1.0f,
	1.0f,  1.0f, 1.0f
};

void Scene::init() {
	objects.clear();

	postProcessing = new Object(new ScreenQuad(), new Material("postBase"));
	postProcessing->material->texture0 = app.textureColorbuffer;
	postProcessing->material->texture1 = app.textureDepthbuffer;
	
	if (id == 0) {
		postProcessing = new Object(new ScreenQuad(), new Material("postKernel"));
		postProcessing->material->texture0 = app.textureColorbuffer;
		postProcessing->material->texture1 = app.textureDepthbuffer;
		std::copy(&edgeKernel[0], &edgeKernel[9], postProcessing->material->u);

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
		o->material->u[0] = 1.0f;
		o->translate(glm::vec3(9.0f, 12.0f, 9.0f));
		o->scale(glm::vec3(2.0f, 2.0f, 2.0f));
		objects.push_back(o);

		o = new Object(new Quad(), new Material());
		o->material->color = glm::vec3(0.5f, 0.5f, 0.5f);
		o->translate(glm::vec3(0.0f, -8.0f, 0.0f));
		o->scale(glm::vec3(20.0f, 1.0f, -10.0f));
		o->rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		objects.push_back(o);
		
		o = new Object(new Cube(), new Material("shaded"));
		o->material->color = glm::vec3(1.0f, 1.0f, 1.0f);
		o->material->u[0] = 0.1f;
		o->material->u[1] = 1.0f;
		o->material->u[2] = 10.0f;
		o->material->u[3] = 5.0f;
		o->translate(glm::vec3(-20.0f, -15.0f, -10.0f));
		o->scale(glm::vec3(6.0f, 6.0f, 6.0f));
		objects.push_back(o);
	}

	for (Object* o : objects) {
		o->init();
	}
	postProcessing->init();
}

void Scene::update() {
	if (id == 0) {
		objects[5]->rotate(90.0f * app.deltaTime, glm::vec3(1.0f, 1.0f, 1.0f));
		objects[10]->material->u[1] = 1.0f*cos(app.time*2.0f);
		objects[10]->material->u[3] = 5.0f*sin(app.time*2.0f);
	}

	for (Object* o : objects) {
		o->update();
	}
	postProcessing->update();
}

void Scene::draw() {
	glBindFramebuffer(GL_FRAMEBUFFER, app.framebuffer);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	for (Object* o : objects) {
		o->draw();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	postProcessing->draw();
}
