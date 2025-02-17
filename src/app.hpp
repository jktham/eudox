#pragma once

#include "resources.hpp"
#include "camera.hpp"
#include "scene.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class App {
public:
	int width = 1920;
	int height = 1080;
	GLFWwindow* window;
	
	unsigned int framebuffer;
	int fbWidth = 1920;
	int fbHeight = 1080;
	unsigned int fbColor;
	unsigned int fbDepthStencil;
	unsigned int fbDepth;
	unsigned int fbPosition;
	unsigned int fbNormal;
	unsigned int fbMask;

	float time;
	float deltaTime;
	float deltaHist[60] = {};
	int frame = 0;
	bool limitFps = true;

	bool firstInput = true;
	glm::ivec2 cursorPos = glm::ivec2(0);
	glm::ivec2 cursorOffset = glm::ivec2(0);

	Resources resources;
	Camera camera;
	Scene scene;

	void init();
	void loop();
	void exit();
};

extern App app;
