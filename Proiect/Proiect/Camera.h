#pragma once

#include <stdio.h>
#include <math.h> 

#include <GL/glew.h>
#include <glfw3.h>

#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include<gtx/rotate_vector.hpp>
#include<gtx/vector_angle.hpp>
#include"Shader.h"
enum ECameraMovementType
{
	UNKNOWN,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
class Camera
{
private:
	// Default camera values
	const float zNEAR = 0.1f;
	const float zFAR = 50000.f;
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float FOV = 45.0f;
	glm::vec3 startPosition;
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

public:
	glm::vec3 position;
	glm::vec3 forward= glm::vec3(0.0f, 0.0f, -1.0f);;
	glm::vec3 right;
	glm::vec3 up= glm::vec3(0.0f, 1.0f, 0.0f);;
	glm::vec3 worldUp;
	bool firstClick = true;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.1f;
	float sensitivity = 100.0f;
	Camera(const int width, const int height, const glm::vec3& position);

	void Set(const int width, const int height, const glm::vec3& position);
	void Reset(const int width, const int height);
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	void Reshape(int windowWidth, int windowHeight);
	const glm::mat4 GetViewMatrix() const;

	const glm::vec3 GetPosition() const;

	const glm::mat4 GetProjectionMatrix() const;

	void ProcessKeyboard(ECameraMovementType direction, float deltaTime);

	void MouseControl(float xPos, float yPos);

	void ProcessMouseScroll(float yOffset);
	void Inputs(GLFWwindow* window);

private:
	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

	void UpdateCameraVectors();

protected:
	const float cameraSpeedFactor = 1.5f;
	const float mouseSensitivity = 0.1f;

	// Perspective properties
	float zNear;
	float zFar;
	float FoVy;
	int width;
	int height;
	bool isPerspective;


	// Euler Angles
	float yaw;
	float pitch;

	bool bFirstMouseMove = true;
	float lastX = 0.f, lastY = 0.f;
};

