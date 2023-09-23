#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

class Renderer {
public:
	unsigned int shader;
	unsigned int vao;
	unsigned int vbo;

	std::vector<float> vertices;

	float time;

	void init();
	void update();
	void draw();

	void generateBuffers();
	void updateBuffers();
	unsigned int compileShader(std::string name);
};
