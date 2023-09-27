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
	
	Object();
	Object(Mesh* mesh, Material* material);
};
