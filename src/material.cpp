#include "material.hpp"

#include "app.hpp"

#include <cstdlib>
#include <glm/glm.hpp>
#include <unordered_set>
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
#include <algorithm>
#include <stdlib.h>

void Material::updateUniforms() {
	// default uniforms
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(parent->model));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(app.camera.view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(app.camera.projection));
	glUniform1f(glGetUniformLocation(shader, "time"), app.scene.time);
	glUniform2f(glGetUniformLocation(shader, "resolution"), app.width, app.height);
	glUniform3f(glGetUniformLocation(shader, "viewPos"), app.camera.position.x, app.camera.position.y, app.camera.position.z);
	glUniformMatrix4fv(glGetUniformLocation(shader, "uiProjection"), 1, GL_FALSE, glm::value_ptr(app.camera.uiProjection));
	glUniformMatrix4fv(glGetUniformLocation(shader, "inverseView"), 1, GL_FALSE, glm::value_ptr(glm::inverse(app.camera.view)));
	glUniform1f(glGetUniformLocation(shader, "fov"), app.camera.fov);

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

	for (auto [key, value] : uniforms) {
		if (std::holds_alternative<int>(value)) {
			glUniform1i(glGetUniformLocation(shader, key.c_str()), std::get<int>(value));
		} else if (std::holds_alternative<float>(value)) {
			glUniform1f(glGetUniformLocation(shader, key.c_str()), std::get<float>(value));
		} else if (std::holds_alternative<glm::vec2>(value)) {
			glUniform2fv(glGetUniformLocation(shader, key.c_str()), 1, glm::value_ptr(std::get<glm::vec2>(value)));
		} else if (std::holds_alternative<glm::vec3>(value)) {
			glUniform3fv(glGetUniformLocation(shader, key.c_str()), 1, glm::value_ptr(std::get<glm::vec3>(value)));
		} else if (std::holds_alternative<glm::vec4>(value)) {
			glUniform4fv(glGetUniformLocation(shader, key.c_str()), 1, glm::value_ptr(std::get<glm::vec4>(value)));
		} else if (std::holds_alternative<glm::mat3>(value)) {
			glUniformMatrix3fv(glGetUniformLocation(shader, key.c_str()), 1, GL_FALSE, glm::value_ptr(std::get<glm::mat3>(value)));
		} else if (std::holds_alternative<glm::mat4>(value)) {
			glUniformMatrix4fv(glGetUniformLocation(shader, key.c_str()), 1, GL_FALSE, glm::value_ptr(std::get<glm::mat4>(value)));
		}
	}

}

unsigned int Material::compileShader(std::string path) {
	if (app.resources.uniforms.contains(path)) {
		uniforms = app.resources.uniforms[path];
	}
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
		getUniforms(geomString);
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
	getUniforms(vertString);
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
	getUniforms(fragString);
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

	app.resources.uniforms[path] = uniforms;
	app.resources.shaders[path] = shader;

	return shader;
}

unsigned int Material::loadTexture(std::string path, bool noInterp) {
	if (app.resources.textures.contains(noInterp ? path + "noInterp" : path)) {
		return app.resources.textures[noInterp ? path + "noInterp" : path];
	}

	int width, height, channels;
	unsigned char *data;

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(("res/textures/" + path).c_str(), &width, &height, &channels, 0);
	if (!data) { // check fonts
		data = stbi_load(("res/fonts/" + path).c_str(), &width, &height, &channels, 0);
	}
	if (data) {
		int format = (channels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (noInterp) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	app.resources.textures[noInterp ? path + "noInterp" : path] = texture;

	return texture;
}

void Material::getUniforms(std::string source) {
	std::unordered_set<std::string> reservedNames = {"model", "view", "projection", "time", "resolution", "viewPos", "uiProjection", "u", "instanceModels", "inverseView", "fov"};

	std::istringstream sourceStream(source);
	std::string line;
	while (std::getline(sourceStream, line)) {
		std::istringstream lineStream(line);
		std::string qualifier;
		lineStream >> qualifier;
		if (qualifier == "uniform") {
			std::string type;
			lineStream >> type;

			std::string name;
			lineStream >> name;
			name = name.substr(0, name.find(";"));
			name = name.substr(0, name.find("["));
			if (reservedNames.find(name) != reservedNames.end()) {
				continue;
			}

			std::string init;
			if (lineStream >> init) {
				std::getline(lineStream, init);
				
				init = init.substr(0, init.find(";"));
				init = init.substr(init.find("(")+1, init.find(")") - init.find("(") - 1);
				std::replace(init.begin(), init.end(), ',', ' ');
				// fmt::println("{}, {}, {}, {}", qualifier, type, name, init);

				std::istringstream initStream(init);
				std::vector<float> values;
				float value;
				while (initStream >> value) {
					values.push_back(value);
				}

				if (type == "int") {
					uniforms[name] = values.size() == 1 ? (int)values[0] : 0;
				} else if (type == "float") {
					uniforms[name] = values.size() == 1 ? values[0] : 0.0f;
				} else if (type == "vec2") {
					uniforms[name] = values.size() == 2 ? glm::vec2(values[0], values[1]) : glm::vec2(values[0]);
				} else if (type == "vec3") {
					uniforms[name] = values.size() == 3 ? glm::vec3(values[0], values[1], values[2]) : glm::vec3(values[0]);
				} else if (type == "vec4") {
					uniforms[name] = values.size() == 4 ? glm::vec4(values[0], values[1], values[2], values[3]) : glm::vec4(values[0]);
				} else if (type == "mat3") {
					uniforms[name] = values.size() == 9 ? glm::mat3(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7], values[8]) : glm::mat3(values[0]);
				} else if (type == "mat4") {
					uniforms[name] = values.size() == 16 ? glm::mat4(values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7], values[8], values[9], values[10], values[11], values[12], values[13], values[14], values[15]) : glm::mat4(values[0]);
				}

			} else {
				if (uniforms.find(name) != uniforms.end()) {
					continue;
				}

				if (type == "int") {
					uniforms[name] = 0;
				} else if (type == "float") {
					uniforms[name] = 0.0f;
				} else if (type == "vec2") {
					uniforms[name] = glm::vec2(0.0f);
				} else if (type == "vec3") {
					uniforms[name] = glm::vec3(0.0f);
				} else if (type == "vec4") {
					uniforms[name] = glm::vec4(0.0f);
				} else if (type == "mat3") {
					uniforms[name] = glm::mat3(0.0f);
				} else if (type == "mat4") {
					uniforms[name] = glm::mat4(0.0f);
				}
			}
			
		}

	}

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
