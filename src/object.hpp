#pragma once

#include "mesh.hpp"
#include "material.hpp"

#include <glm/glm.hpp>
#include <vector>

class Mesh;
class Material;

class Object {
public:
	Mesh* mesh;
	Material* material;
	glm::mat4 model = glm::mat4(1.0f);

	virtual void draw();
	void translate(glm::vec3 offset);
	void scale(glm::vec3 factor);
	void rotate(float angle, glm::vec3 axis);

	Object();
	Object(Mesh* mesh, Material* material);
};

class InstancedObject : public Object {
public:
	std::vector<glm::mat4> instanceModels = {};

	virtual void draw();

	InstancedObject();
	InstancedObject(Mesh* mesh, Material* material);
};
