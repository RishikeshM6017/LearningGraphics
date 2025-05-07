#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtx/vector_angle.hpp>

#include "Shader.h"

class Camera
{
public:
	Camera(int width, int height, glm::vec3 position);

public:
	void Link(Shader& shader, const char* uniform);
	void UpdateMatrix(float FOV, float near, float far);
	void Inputs(GLFWwindow* window);


public:
	glm::vec3 position;
	glm::vec3 orientation	= glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up			= glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix  = glm::mat4(1.0f);

	int width;
	int height;

	float speed = 0.01f;
	float sensitivity = 100.0f;

	bool firstClick = true;

};

