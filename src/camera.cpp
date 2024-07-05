#include "camera.hpp"

#include "app.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

void Camera::init() {
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::perspective(fov / 180.0f * 3.14f, (float)app.width / (float)app.height, 0.1f, 1000.0f);
}

void Camera::update() {
	pitch -= (app.cursorOffset.y) * sensitivity;
	yaw += (app.cursorOffset.x) * sensitivity;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	if (yaw < 0.0f) {
		yaw += 360.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(direction);
	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));

	float d = speed * app.deltaTime;
	if (glfwGetKey(app.window, GLFW_KEY_LEFT_SHIFT)) {
		d *= 10.0f;
	}
	if (glfwGetKey(app.window, GLFW_KEY_LEFT_CONTROL)) {
		d *= 0.1f;
	}
	if (glfwGetKey(app.window, GLFW_KEY_W)) {
		position += d * front;
	}
	if (glfwGetKey(app.window, GLFW_KEY_S)) {
		position -= d * front;
	}
	if (glfwGetKey(app.window, GLFW_KEY_D)) {
		position += d * right;
	}
	if (glfwGetKey(app.window, GLFW_KEY_A)) {
		position -= d * right;
	}
	if (glfwGetKey(app.window, GLFW_KEY_R)) {
		position += d * up;
	}
	if (glfwGetKey(app.window, GLFW_KEY_F)) {
		position -= d * up;
	}

	view = glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective((float)glm::radians(fov), (float)app.width / (float)app.height, 0.1f, 1000.0f);
	uiProjection = glm::ortho(0.0f, (float)app.width, 0.0f, (float)app.height, -100.0f, 100.0f);
}
