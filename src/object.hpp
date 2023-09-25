#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

class Object {
public:
	unsigned int shader;
	unsigned int vao;
	unsigned int vbo;

	std::vector<float> vertices = {};
	int stride = 11;
	std::string shaderName = "base";
	glm::mat4 model = glm::mat4(1.0f);

	void init();
	void update();
	void draw();

	void updateUniforms();
	void generateBuffers();
	void updateBuffers();
	unsigned int compileShader(std::string name);

	virtual std::vector<float> getVertices();
};

class Cube : public Object {
public:
	glm::vec3 color = glm::vec3(1.0f);

	std::vector<float> getVertices();
};

class Quad : public Object {
public:
	glm::vec3 color = glm::vec3(1.0f);

	std::vector<float> getVertices();
};
