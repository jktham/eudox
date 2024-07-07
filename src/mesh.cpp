#include "mesh.hpp"
#include "app.hpp"
#include "data.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include <sstream>

void Mesh::generateBuffers() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0); // position xyz
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float))); // normal xyz
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float))); // color rgb
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float))); // texcoord uv
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);
}

void Mesh::updateBuffers(std::vector<float> vertices) {
	triangles = vertices.size() / 11;

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

std::vector<float> Mesh::loadModel(std::string path) {
	std::vector<float> vertices = {};
	std::ifstream file("res/models/" + path);
	std::string line;

	std::vector<std::vector<float>> positions = {};
	std::vector<std::vector<float>> normals = {};
	std::vector<std::vector<float>> texcoords = {};
	std::vector<std::vector<int>> faces = {};

	while (std::getline(file, line)) {
		std::replace(line.begin(), line.end(), '/', ' ');
		std::istringstream ss(line);
		std::string label;
		ss >> label;

		if (label == "v") {
			std::string tokens[3];
			std::vector<float> v = {};
			for (int i=0; i<3; i++) {
				ss >> tokens[i];
				v.push_back(std::stof(tokens[i]));
			}
			positions.push_back(v);

		} else if (label == "vn") {
			std::string tokens[3];
			std::vector<float> v = {};
			for (int i=0; i<3; i++) {
				ss >> tokens[i];
				v.push_back(std::stof(tokens[i]));
			}
			normals.push_back(v);

		} else if (label == "vt") {
			std::string tokens[2];
			std::vector<float> v = {};
			for (int i=0; i<2; i++) {
				ss >> tokens[i];
				v.push_back(std::stof(tokens[i]));
			}
			texcoords.push_back(v);

		} else if (label == "f") {
			std::string tokens[9];
			std::vector<int> v = {};
			for (int i=0; i<9; i++) {
				ss >> tokens[i];
				v.push_back(std::stoi(tokens[i]));
			}
			faces.push_back(v);

		}
	}

	for (int i=0; i<faces.size(); i++) {
		for (int j=0; j<3; j++) {
			std::vector<float> vert = {
				positions[faces[i][0+3*j]-1][0], positions[faces[i][0+3*j]-1][1], positions[faces[i][0+3*j]-1][2],
				normals[faces[i][2+3*j]-1][0], normals[faces[i][2+3*j]-1][1], normals[faces[i][2+3*j]-1][2],
				1.0f, 1.0f, 1.0f,
				texcoords[faces[i][1+3*j]-1][0], texcoords[faces[i][1+3*j]-1][1]
			};
			for (int k=0; k<vert.size(); k++) {
				vertices.push_back(vert[k]);
			}
		}
	}

	return vertices;
}

Mesh::Mesh() {
	generateBuffers();
	updateBuffers(triangle);
}

Mesh::Mesh(std::vector<float> vertices) {
	generateBuffers();
	updateBuffers(vertices);
}

Mesh::Mesh(std::string modelPath) {
	if (app.resources.meshes.contains(modelPath)) {
		vao = std::get<0>(app.resources.meshes[modelPath]);
		vbo = std::get<1>(app.resources.meshes[modelPath]);
		triangles = std::get<2>(app.resources.meshes[modelPath]);
		return;
	}

	generateBuffers();
	updateBuffers(loadModel(modelPath));

	app.resources.meshes[modelPath] = {vao, vbo, triangles};
}
