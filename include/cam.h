#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
	FORWARD, BACKWARD, LEFT, RIGHT
};

const float YAW = -90.f;
const float PITCH = 0.0f;
const float SPEED = 10.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

const int screenWidth = 1920;
const int screenHeight = 1080;


struct Cam {
public:
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw = YAW;
	float pitch = PITCH;
	float movementSpeed = SPEED;
	float mouseSensitivity = SENSITIVITY;
	float zoom = ZOOM;

	Cam() {
		worldUp = up;
		updateVecs();
	}

	void update() {
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(zoom), float(screenWidth) / float(screenHeight), 0.1f, 100.0f);

		glm::mat4 view;
		float camX = sin(glfwGetTime()) * 10.0f;
		float camZ = cos(glfwGetTime()) * 10.0f;
		view = glm::lookAt(pos, pos + front, up);
	}

	glm::mat4 getView() {
		return glm::lookAt(pos, pos + front, up);
	}

	void processInput(CameraMovement direction, float deltaTime) {
		float vel = movementSpeed * deltaTime;
		if (direction == FORWARD)
			pos += front * vel;
		if (direction == BACKWARD)
			pos -= front * vel;
		if (direction == LEFT)
			pos -= right * vel;
		if (direction == RIGHT)
			pos += right * vel;
	}

	void updateMouse(double xoffset, double yoffset) {
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		updateVecs();
	}

	void updateZoom(double xoffset, double yoffset) {
		zoom -= (float)yoffset;
		if (zoom < 1.0f)
			zoom = 1.0f;
		if (zoom > 45.0f)
			zoom = 45.0f;
	}

private:
	void updateVecs() {
		glm::vec3 newFront;
		newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		newFront.y = sin(glm::radians(pitch));
		newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(newFront);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
};