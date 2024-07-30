#include "material.hpp"

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
#include <stb/stb_image.h>
#include <sstream>

void Material::updateUniforms() {
	// default uniforms
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(parent->model));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(app.camera.view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(app.camera.projection));
	glUniform1f(glGetUniformLocation(shader, "time"), app.scene.time);
	glUniform2f(glGetUniformLocation(shader, "resolution"), app.width, app.height);
	glUniform3f(glGetUniformLocation(shader, "color"), color.r, color.g, color.b);
	glUniform3f(glGetUniformLocation(shader, "light"), light.x, light.y, light.z);
	glUniform3f(glGetUniformLocation(shader, "viewPos"), app.camera.position.x, app.camera.position.y, app.camera.position.z);
	glUniformMatrix4fv(glGetUniformLocation(shader, "uiProjection"), 1, GL_FALSE, glm::value_ptr(app.camera.uiProjection));

	// custom uniforms
	// 0-15: frag
	// 16-23: vert
	// 24-31: geom
	glUniform1fv(glGetUniformLocation(shader, "u"), 32, &u[0]);

	// textures
	for (int i=0; i<32; i++) {
		if (textures[i]) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
		}
	}

}

unsigned int Material::compileShader(std::string path) {
	if (app.resources.shaders.contains(path)) {
		return app.resources.shaders[path];
	}

	std::istringstream pathStream(path);
	std::vector<std::string> paths = {};
	for (int i=0; i<3; i++) {
		std::string token;
		if (pathStream >> token) {
			paths.push_back(token);
		}
	}

	// default to world/
	for (int i=0; i<paths.size(); i++) {
		if (paths[i].find("/") == std::string::npos) {
			paths[i] = "world/" + paths[i];
		}
	}

	std::string p = paths[0];
	if (paths.size() == 3) {
		p = paths[1];
	}

	int success = 0;
	unsigned int shader = glCreateProgram();

	const char *geomSource;
	std::ifstream geomFile("res/shaders/" + p + ".geom");
	if (geomFile.good()) { // only if exists
		std::string geomString((std::istreambuf_iterator<char>(geomFile)), std::istreambuf_iterator<char>());
		geomSource = geomString.c_str();
		unsigned int geomShader;
		geomShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geomShader, 1, &geomSource, NULL);
		glCompileShader(geomShader);

		success = 0;
		glGetShaderiv(geomShader, GL_COMPILE_STATUS, &success);
		if (success == 0) {
			int logSize = 0;
			glGetShaderiv(geomShader, GL_INFO_LOG_LENGTH, &logSize);
			std::vector<char> errorLog(logSize);
			glGetShaderInfoLog(geomShader, logSize, &logSize, &errorLog.front());
			std::cout << errorLog.data() << std::endl;
		}

		glAttachShader(shader, geomShader);
		glDeleteShader(geomShader);
	}

	if (paths.size() == 3 || paths.size() == 2) {
		p = paths[0];
	}

	const char *vertSource;
	std::ifstream vertFile("res/shaders/" + p + ".vert");
	if (!vertFile.good()) { // default to base
		std::string pathdir = p.substr(0, p.find_last_of("/") + 1);
		vertFile = std::ifstream("res/shaders/" + pathdir + "base.vert");
	}
	std::string vertString((std::istreambuf_iterator<char>(vertFile)), std::istreambuf_iterator<char>());
	if (geomFile.good()) { // insert preprocessor define
		vertString.insert(vertString.find("\n", vertString.find("#version"))+1, "#define HASGEOMSTAGE\n");
	}
	vertSource = vertString.c_str();
	unsigned int vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSource, NULL);
	glCompileShader(vertShader);

	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (success == 0) {
		int logSize = 0;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<char> errorLog(logSize);
		glGetShaderInfoLog(vertShader, logSize, &logSize, &errorLog.front());
		std::cout << errorLog.data() << std::endl;
	}

	if (paths.size() == 3 || paths.size() == 2) {
		p = paths[paths.size()-1];
	}

	const char *fragSource;
	std::ifstream fragFile("res/shaders/" + p + ".frag");
	if (!fragFile.good()) { // default to base
		std::string pathdir = p.substr(0, p.find_last_of("/") + 1);
		fragFile = std::ifstream("res/shaders/" + pathdir + "base.frag");
	}
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

	glAttachShader(shader, vertShader);
	glAttachShader(shader, fragShader);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	glLinkProgram(shader);

	app.resources.shaders[path] = shader;

	return shader;
}

unsigned int Material::loadTexture(std::string path) {
	if (app.resources.textures.contains(path)) {
		return app.resources.textures[path];
	}

	int width, height, channels;
	unsigned char *data;

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(("res/textures/" + path).c_str(), &width, &height, &channels, 0);
	if (data) {
		int format = (channels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	app.resources.textures[path] = texture;

	return texture;
}

Material::Material() {
	shader = compileShader("world/base");
}

Material::Material(std::string shaderPath) {
	shader = compileShader(shaderPath);
}

Material::Material(std::string shaderPath, std::string texturePath) {
	shader = compileShader(shaderPath);
	textures[0] = loadTexture(texturePath);
}
