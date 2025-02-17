#include "app.hpp"

#include "camera.hpp"
#include "fmt/base.h"
#include "scene.hpp"

#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fmt/core.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#include <ctime>

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	app.cursorOffset = glm::ivec2(xpos, ypos) - app.cursorPos;
	app.cursorPos = glm::ivec2(xpos, ypos);
	if (app.firstInput) {
		app.firstInput = false;
		app.cursorOffset = glm::ivec2(0);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9 && action == GLFW_PRESS) {
		if (glfwGetKey(app.window, GLFW_KEY_LEFT_SHIFT)) {
			app.scene.postId = key - GLFW_KEY_0;
			app.scene.initPost();
		} else {
			app.scene.sceneId = key - GLFW_KEY_0;
			app.scene.init();
		}
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		if (glfwGetKey(app.window, GLFW_KEY_LEFT_SHIFT)) {
			app.scene.postId--;
			if (app.scene.postId < 1) app.scene.postId = 1;
			app.scene.initPost();
		} else {
			app.scene.sceneId--;
			if (app.scene.sceneId < 1) app.scene.sceneId = 1;
			app.scene.init();
		}
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		if (glfwGetKey(app.window, GLFW_KEY_LEFT_SHIFT)) {
			app.scene.postId++;
			app.scene.initPost();
		} else {
			app.scene.sceneId++;
			app.scene.init();
		}
	}
	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		unsigned char *data = (unsigned char*)malloc(app.width * app.height * 4);
		glReadPixels(0, 0, app.width, app.height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		std::time_t time = std::time(nullptr);
		stbi_flip_vertically_on_write(true);
		stbi_write_png(fmt::format("img/{}.png", time).c_str(), app.width, app.height, 4, data, app.fbWidth * 4);
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		app.scene.paused = !app.scene.paused;
	}
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		app.limitFps = !app.limitFps;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset > 0.0) {
		app.camera.fov *= 0.8f;
		app.camera.sensitivity *= 0.8f;
	}
	if (yoffset < 0.0) {
		app.camera.fov *= 1.25f;
		app.camera.sensitivity *= 1.25f;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	app.width = width;
	app.height = height;
	// glViewport(0, 0, width, height);
}

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam) {
	
	if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " <<  message << std::endl;

	switch (source) {
		case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type) {
		case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
		case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;
	
	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
		case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
		case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

void App::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, "euclid", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
	// glDebugMessageCallback(glDebugOutput, nullptr);
	// glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	glfwSwapInterval(0);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);

	// glEnable(GL_BLEND); // funky
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLineWidth(1.0f);
	glPointSize(1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &fbColor);
	glBindTexture(GL_TEXTURE_2D, fbColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fbWidth, fbHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbColor, 0);

	glGenTextures(1, &fbDepthStencil);
	glBindTexture(GL_TEXTURE_2D, fbDepthStencil);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, fbWidth, fbHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, fbDepthStencil, 0);

	glGenTextures(1, &fbDepth);
	glBindTexture(GL_TEXTURE_2D, fbDepth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, fbWidth, fbHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, fbDepth, 0);

	glGenTextures(1, &fbPosition);
	glBindTexture(GL_TEXTURE_2D, fbPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, fbWidth, fbHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, fbPosition, 0);

	glGenTextures(1, &fbNormal);
	glBindTexture(GL_TEXTURE_2D, fbNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, fbWidth, fbHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, fbNormal, 0);

	glGenTextures(1, &fbMask);
	glBindTexture(GL_TEXTURE_2D, fbMask);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8UI, fbWidth, fbHeight, 0, GL_RGB_INTEGER, GL_UNSIGNED_INT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, fbMask, 0);
	
	unsigned int attachments[5] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4};
	glDrawBuffers(5, attachments);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	camera.init();
	scene.init();
}

void App::loop() {
	while (!glfwWindowShouldClose(window)) {
		deltaTime = glfwGetTime() - time;
		if (limitFps && deltaTime < 1.0f / 120.0f) {
			continue;
		}

		time = glfwGetTime();
		deltaHist[frame % 60] = deltaTime;
		frame++;

		float deltaSum = 0.0001f;
		for (int i = 0; i < 60; i++) {
			deltaSum += deltaHist[i];
		}

		glfwPollEvents();
		processInput(window);

		camera.update();
		scene.update();
		scene.draw();

		float elapsedTime = glfwGetTime() - time;
		fmt::print(
			"f: {}, t: {:.4f}, dt: {:.4f}, et: {:.6f}, fps: {:.2f}, pos: ({:.2f}, {:.2f}, {:.2f}), res: ({}, {}, {}), id: ({}, {})\n", 
			frame, time, deltaTime, elapsedTime, 1.0f / (deltaSum / 60.0f), camera.position.x, camera.position.y, camera.position.z, 
			resources.shaders.size(), resources.textures.size(), resources.meshes.size(), scene.sceneId, scene.postId
		);

		glfwSwapBuffers(window);
	}
}

void App::exit() {
	glfwTerminate();
}
