#pragma once

#include "mesh.hpp"
#include "material.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <string>

class Mesh;
class Material;

class Object {
public:
	Mesh* mesh;
	Material* material;
	glm::mat4 model = glm::mat4(1.0f);

	void init();
	void update();
	void draw();

	void translate(glm::vec3 offset);
	void scale(glm::vec3 factor);
	void rotate(float angle, glm::vec3 axis);

	Object();
	Object(Mesh* mesh, Material* material);
};
