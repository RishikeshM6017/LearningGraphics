#define GLFW_INCLUDE_VULKAN

#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "Application.h"

#define WINDOW_WIDTH 540
#define WINDOW_HEIGHT 540

GLFWwindow* window = NULL;

void OnKeyInput(GLFWwindow* windwo, int key, int scancode, int action, int mods)
{
	if ((key == GLFW_KEY_F8) && (action == GLFW_PRESS))
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}


int main()
{
	if (!glfwInit())
	{
		return -1;
	}

	if (!glfwVulkanSupported())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan Engine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, OnKeyInput);

	Application app;
	app.Initialize("Vulkan Application", window);

	while (!glfwWindowShouldClose(window))
	{
		app.Render();
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}