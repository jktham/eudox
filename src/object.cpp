#include "object.hpp"

#include <glm/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Object::draw() {
	glUseProgram(material->shader);
	glBindVertexArray(mesh->vao);

	material->updateUniforms();

	glDrawArrays(GL_TRIANGLES, 0, mesh->triangles);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Object::translate(glm::vec3 offset) {
	model = glm::translate(model, offset);
}

void Object::scale(glm::vec3 factor) {
	model = glm::scale(model, factor);
}

void Object::rotate(float angle, glm::vec3 axis) {
	model = glm::rotate(model, angle / 180.0f * 3.1415f, glm::normalize(axis));
}

Object::Object() {
	
}

Object::Object(Mesh* mesh, Material* material) {
	this->mesh = mesh;
	this->material = material;
	this->mesh->parent = this;
	this->material->parent = this;
}

void InstancedObject::draw() {
	glUseProgram(material->shader);
	glBindVertexArray(mesh->vao);

	material->updateUniforms();

	// todo: use buffer
	glUniformMatrix4fv(glGetUniformLocation(material->shader, "instanceModels"), instanceModels.size(), GL_FALSE, glm::value_ptr(instanceModels.front()));

	glDrawArraysInstanced(GL_TRIANGLES, 0, mesh->triangles, instanceModels.size());

	glBindVertexArray(0);
	glUseProgram(0);
}

InstancedObject::InstancedObject() {

}

InstancedObject::InstancedObject(Mesh* mesh, Material* material) {
	this->mesh = mesh;
	this->material = material;
	this->mesh->parent = this;
	this->material->parent = this;

}
