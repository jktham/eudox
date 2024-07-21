#include "scene.hpp"

#include "app.hpp"
#include "glm/fwd.hpp"
#include "object.hpp"
#include "data.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/gl.h>

float rnd(float min, float max) {
	return min + (float)std::rand() / ((float)RAND_MAX/(max-min));
}

void Scene::init() {
	worldObjects.clear();
	uiObjects.clear();
	Object* o;
	
	if (sceneId == 1) {
		glm::vec3 light = glm::vec3(100.0f*cos(time*2.0f), 200.0f, 100.0f*sin(time*2.0f));

		o = new Object(new Mesh(), new Material());
		o->translate(glm::vec3(0.0f, 0.0f, 0.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(triangle), new Material("textured", "test.png"));
		o->translate(glm::vec3(-1.0f, 5.0f, -8.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(), new Material());
		o->translate(glm::vec3(3.0f, -4.0f, -6.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh(cube), new Material("textured", "test.png"));
		o->material->color = glm::vec3(1.0f, 0.0f, 0.0f);
		o->translate(glm::vec3(0.0f, 0.0f, -10.0f));
		o->scale(glm::vec3(1.0f, 2.0f, 1.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(cube), new Material());
		o->material->color = glm::vec3(0.0f, 0.0f, 1.0f);
		o->translate(glm::vec3(5.0f, 2.0f, -5.0f));
		o->scale(glm::vec3(3.0f, 1.0f, 1.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(cube), new Material("outline"));
		o->material->color = glm::vec3(1.0f, 0.0f, 1.0f);
		o->translate(glm::vec3(-3.0f, -1.0f, -4.0f));
		o->scale(glm::vec3(0.8f, 0.8f, 0.8f));
		o->rotate(90.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(cube), new Material("outline"));
		o->material->color = glm::vec3(1.0f, 1.0f, 1.0f);
		o->translate(glm::vec3(0.0f, 10.0f, 0.0f));
		o->scale(glm::vec3(20.0f, 20.0f, 20.0f));
		worldObjects.push_back(o);
		
		o = new Object(new Mesh(cube), new Material("outline"));
		o->material->color = glm::vec3(1.0f, 1.0f, 1.0f);
		o->translate(glm::vec3(9.0f, 10.0f, 9.0f));
		o->scale(glm::vec3(2.0f, 2.0f, 2.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh(cube), new Material("rainbow"));
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
		
		o = new Object(new Mesh(cube), new Material("shaded"));
		o->material->color = glm::vec3(1.0f, 1.0f, 1.0f);
		o->material->light = light;
		o->translate(glm::vec3(0.0f, -10.0f, 0.0f));
		o->scale(glm::vec3(4.0f, 4.0f, 4.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("shaded"));
		o->material->light = light;
		o->translate(glm::vec3(-10.0f, 0.0f, -10.0f));
		o->scale(glm::vec3(4.0f, 4.0f, 4.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("explode shadedtextured", "test.png"));
		o->material->light = light;
		o->translate(glm::vec3(-20.0f, 0.0f, -10.0f));
		o->scale(glm::vec3(2.0f, 2.0f, 2.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("icosphere.obj"), new Material("wireframe"));
		o->translate(glm::vec3(-10.0f, 0.0f, 10.0f));
		o->scale(glm::vec3(1.0f, 1.0f, 1.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("torus.obj"), new Material("wireframe"));
		o->translate(glm::vec3(-10.0f, 0.0f, 10.0f));
		o->scale(glm::vec3(2.0f, 2.0f, 2.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monkesmooth.obj"), new Material("noise"));
		o->translate(glm::vec3(-20.0f, 0.0f, 10.0f));
		o->scale(glm::vec3(1.0f, 1.0f, 1.0f));
		o->rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("ngon.obj"), new Material("textured", "test.png"));
		o->translate(glm::vec3(-30.0f, 0.0f, 10.0f));
		o->scale(glm::vec3(2.0f, 2.0f, 2.0f));
		o->rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
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

	} else if (sceneId == 2) {
		glm::vec3 light = glm::vec3(100.0f*cos(time*2.0f), 200.0f, 100.0f*sin(time*2.0f));

		InstancedObject* o;
		o = new InstancedObject(new Mesh("monkesmooth.obj"), new Material("instanced shadedtextured", "test.png"));
		o->material->light = light;
		for (int i = 0; i < 200; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(rnd(-20.0f, 20.0f), rnd(-20.0f, 20.0f), rnd(-20.0f, 20.0f)));
			model = glm::rotate(model, rnd(0.0f, 360.0f), glm::vec3(rnd(0.0f, 1.0f), rnd(0.0f, 1.0f), rnd(0.0f, 1.0f)));
			o->instanceModels.push_back(model);
		}
		worldObjects.push_back(o);

		o = new InstancedObject(new Mesh("monkesmooth.obj"), new Material("instanced shadedtextured", "test.png"));
		o->material->light = light;
		for (int i = 0; i < 200; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(rnd(-20.0f, 20.0f), rnd(-20.0f, 20.0f), rnd(-20.0f, 20.0f)));
			model = glm::rotate(model, rnd(0.0f, 360.0f), glm::vec3(rnd(0.0f, 1.0f), rnd(0.0f, 1.0f), rnd(0.0f, 1.0f)));
			o->instanceModels.push_back(model);
		}
		worldObjects.push_back(o);

	} else if (sceneId == 3) {
		glm::vec3 light = glm::vec3(100.0f, 150.0f, 200.0f);

		o = new Object(new Mesh("monke.obj"), new Material("base"));
		o->translate(glm::vec3(0.0f, 0.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("textured", "test.png"));
		o->translate(glm::vec3(5.0f, 0.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("shaded"));
		o->material->light = light;
		o->translate(glm::vec3(10.0f, 0.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("shadedtextured", "test.png"));
		o->material->light = light;
		o->translate(glm::vec3(15.0f, 0.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("rainbow"));
		o->material->u[0] = 1.0f;
		o->translate(glm::vec3(20.0f, 0.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("noise"));
		o->translate(glm::vec3(25.0f, 0.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("explode shadedtextured", "test.png"));
		o->material->light = light;
		o->translate(glm::vec3(0.0f, 5.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("shadedtextured", "test.png"));
		o->material->light = light;
		o->translate(glm::vec3(5.0f, 5.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("base visnormals normal"));
		o->translate(glm::vec3(5.0f, 5.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monkesmooth.obj"), new Material("base visnormals normal"));
		o->translate(glm::vec3(10.0f, 5.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monkesmooth.obj"), new Material("wireframe"));
		o->translate(glm::vec3(15.0f, 5.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monkesmooth.obj"), new Material("points"));
		o->translate(glm::vec3(20.0f, 5.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("base wireframe shadedtextured", "test.png"));
		o->material->light = light;
		o->translate(glm::vec3(25.0f, 5.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("glitch shadedtextured", "test.png"));
		o->material->light = light;
		o->translate(glm::vec3(0.0f, 10.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monkesmooth.obj"), new Material("glitch shadedtextured", "test.png"));
		o->material->light = light;
		o->translate(glm::vec3(5.0f, 10.0f, -10.0f));
		worldObjects.push_back(o);

		for (int i = 0; i < 20; i++) {
			o = new Object(new Mesh("monkesmooth.obj"), new Material("base points noise"));
			o->translate(glm::vec3(10.0f + (i-10)/200.0f, 10.0f, -10.0f));
			worldObjects.push_back(o);
		}

		o = new Object(new Mesh("monkesmooth.obj"), new Material("ripple shadedtextured", "test.png"));
		o->material->light = light;
		o->translate(glm::vec3(15.0f, 10.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monkesmooth.obj"), new Material("ripple wireframe rainbow"));
		o->material->u[0] = 2.0f;
		o->material->u[16] = 20.0f;
		o->material->u[19] = 0.1f;
		o->translate(glm::vec3(20.0f, 10.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monkesmooth.obj"), new Material("glitch wireframe noise"));
		o->material->u[0] = 4.0f;
		o->material->u[16] = 20.0f;
		o->translate(glm::vec3(25.0f, 10.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monke.obj"), new Material("ripple wireframe normal"));
		o->material->u[16] = 6.0f;
		o->material->u[17] = 2.0f;
		o->material->u[18] = 8.0f;
		o->material->u[19] = 0.1f;
		o->translate(glm::vec3(0.0f, 15.0f, -10.0f));
		worldObjects.push_back(o);

		o = new Object(new Mesh("monkesmooth.obj"), new Material("base points circle"));
		o->material->u[24] = 16.0f;
		o->translate(glm::vec3(5.0f, 15.0f, -10.0f));
		worldObjects.push_back(o);

	}

	initPost();
}

void Scene::initPost() {
	if (postId == 1) {
		// use scene default
		if (sceneId == 1) {
			post = new Object(new Mesh(quad), new Material("post/kernel"));
			post->scale(glm::vec3(app.width, app.height, 1.0f));
			post->material->textures[0] = app.fbColor;
			post->material->textures[1] = app.fbDepth;
			post->material->textures[2] = app.fbPosition;
			post->material->textures[3] = app.fbNormal;
			std::copy(&edgeKernel[0], &edgeKernel[9], post->material->u);
		
		} else if (sceneId == 2) {
			post = new Object(new Mesh(quad), new Material("post/distort"));
			post->scale(glm::vec3(app.width, app.height, 1.0f));
			post->material->textures[0] = app.fbColor;
			post->material->textures[1] = post->material->loadTexture("distortSpiral.png");
			
		} else if (sceneId == 3) {
			post = new Object(new Mesh(quad), new Material("post/base"));
			post->scale(glm::vec3(app.width, app.height, 1.0f));
			post->material->textures[0] = app.fbColor;
			post->material->textures[1] = app.fbDepth;
			post->material->textures[2] = app.fbPosition;
			post->material->textures[3] = app.fbNormal;

		}
		
	} else if (postId == 2) {
		post = new Object(new Mesh(quad), new Material("post/base"));
		post->scale(glm::vec3(app.width, app.height, 1.0f));
		post->material->textures[0] = app.fbColor;

	} else if (postId == 3) {
		post = new Object(new Mesh(quad), new Material("post/kernel"));
		post->scale(glm::vec3(app.width, app.height, 1.0f));
		post->material->textures[0] = app.fbNormal;
		std::copy(&edgeKernel[0], &edgeKernel[9], post->material->u);

	} else if (postId == 4) {
		post = new Object(new Mesh(quad), new Material("post/distort"));
		post->scale(glm::vec3(app.width, app.height, 1.0f));
		post->material->textures[0] = app.fbColor;
		post->material->textures[1] = post->material->loadTexture("distortDamascus.png");

	} else if (postId == 5) {
		post = new Object(new Mesh(quad), new Material("post/pixel"));
		post->scale(glm::vec3(app.width, app.height, 1.0f));
		post->material->textures[0] = app.fbColor;

	} else if (postId == 6) {
		post = new Object(new Mesh(quad), new Material("post/invert"));
		post->scale(glm::vec3(app.width, app.height, 1.0f));
		post->material->textures[0] = app.fbColor;

	} else if (postId == 7) {
		post = new Object(new Mesh(quad), new Material("post/sonar"));
		post->scale(glm::vec3(app.width, app.height, 1.0f));
		post->material->textures[0] = app.fbColor;
		post->material->textures[1] = app.fbPosition;

	} else if (postId == 8) {
		post = new Object(new Mesh(quad), new Material("post/dither"));
		post->scale(glm::vec3(app.width, app.height, 1.0f));
		post->material->textures[0] = app.fbColor;
		post->material->textures[1] = post->material->loadTexture("ditherTest.png");

	}
}

void Scene::update() {
	if (paused) {
		return;
	}

	deltaTime = app.deltaTime;
	time += deltaTime;

	if (sceneId == 1) {
		glm::vec3 light = glm::vec3(100.0f*cos(time*2.0f), 200.0f, 100.0f*sin(time*2.0f));
		worldObjects[5]->rotate(90.0f * deltaTime, glm::vec3(1.0f, 1.0f, 1.0f));
		worldObjects[10]->material->light = light;
		worldObjects[11]->material->light = light;
		worldObjects[12]->material->light = light;
		worldObjects[13]->rotate(-90.0f * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		worldObjects[14]->rotate(60.0f * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
		uiObjects[0]->rotate(90.0f * deltaTime, glm::vec3(1.0f, 1.0f, 1.0f));

	} else if (sceneId == 2) {
		glm::vec3 light = glm::vec3(100.0f*cos(time*2.0f), 200.0f, 100.0f*sin(time*2.0f));
		worldObjects[0]->material->light = light;
		worldObjects[1]->material->light = light;

	}
}

void Scene::draw() {
	glBindFramebuffer(GL_FRAMEBUFFER, app.framebuffer);
	glViewport(0, 0, app.fbWidth, app.fbHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	for (Object* o : worldObjects) {
		o->draw();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, app.width, app.height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	post->draw();

	glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	for (Object* o : uiObjects) {
		o->draw();
	}
}
