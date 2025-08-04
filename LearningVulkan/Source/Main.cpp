#define GLFW_INCLUDE_VULKAN

#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 540
#define WINDOW_HEIGHT 540

GLFWwindow* window = NULL;

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

	if (window == NULL)
	{
		return -1;
	}
}