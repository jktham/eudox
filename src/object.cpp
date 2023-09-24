#include "object.hpp"

#include "app.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Object::init() {
	shader = compileShader(shaderName);
	generateBuffers();
	updateBuffers();
}

void Object::update() {
	updateBuffers();
}

void Object::draw() {
	glUseProgram(shader);
	glBindVertexArray(vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(app.camera.view));
	glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(app.camera.projection));

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / stride);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Object::generateBuffers() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0); // position xyz
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float))); // normal xyz
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float))); // color rgb
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(9 * sizeof(float))); // texcoord uv
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);
}

void Object::updateBuffers() {
	vertices = getVertices();

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

unsigned int Object::compileShader(std::string name) {
	const char *vertSource;
	std::ifstream vertFile("res/" + name + ".vert");
	std::string vertString((std::istreambuf_iterator<char>(vertFile)), std::istreambuf_iterator<char>());
	vertSource = vertString.c_str();
	unsigned int vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSource, NULL);
	glCompileShader(vertShader);

	int success;
	success = 0;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (success == 0) {
		int logSize = 0;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<char> errorLog(logSize);
		glGetShaderInfoLog(vertShader, logSize, &logSize, &errorLog.front());
		std::cout << errorLog.data() << std::endl;
	}

	const char *fragSource;
	std::ifstream fragFile("res/" + name + ".frag");
	std::string fragString((std::istreambuf_iterator<char>(fragFile)), std::istreambuf_iterator<char>());
	fragSource = fragString.c_str();
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, NULL);
	glCompileShader(fragShader);

	success = 0;
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (success == 0) {
		int logSize = 0;
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<char> errorLog(logSize);
		glGetShaderInfoLog(fragShader, logSize, &logSize, &errorLog.front());
		std::cout << errorLog.data() << std::endl;
	}

	unsigned int shader = glCreateProgram();
	glAttachShader(shader, vertShader);
	glAttachShader(shader, fragShader);
	glLinkProgram(shader);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return shader;
}

std::vector<float> Object::getVertices() {
	std::vector<float> vertices = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.8f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	};
	return vertices;
}

std::vector<float> Cube::getVertices() {
	std::vector<float> vertices = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, color.r, color.g, color.b, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, color.r, color.g, color.b, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, color.r, color.g, color.b, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, color.r, color.g, color.b, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, color.r, color.g, color.b, 0.0f, 0.0f,
		0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 0.0f, 0.0f,
		0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, color.r, color.g, color.b, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, color.r, color.g, color.b, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, color.r, color.g, color.b, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, color.r, color.g, color.b, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, color.r, color.g, color.b, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, color.r, color.g, color.b, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, color.r, color.g, color.b, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, color.r, color.g, color.b, 0.0f, 1.0f
	};
	return vertices;
}

std::vector<float> Quad::getVertices() {
	std::vector<float> vertices = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, color.r, color.g, color.b, 0.0f, 0.0f
	};
	return vertices;
}
