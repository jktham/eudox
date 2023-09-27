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

void Object::init()
{
	mesh->parent = this;
	mesh->vertices = mesh->getVertices();
	mesh->generateBuffers();
	mesh->updateBuffers();

	material->parent = this;
	material->shader = material->compileShader(material->shaderName);
}

void Object::update() {
	
}

void Object::draw() {
	glUseProgram(material->shader);
	glBindVertexArray(mesh->vao);

	material->updateUniforms();

	glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size() / mesh->stride);

	glBindVertexArray(0);
	glUseProgram(0);
}

Object::Object() {
	
}

Object::Object(Mesh* mesh, Material* material) {
	this->mesh = mesh;
	this->material = material;
}
