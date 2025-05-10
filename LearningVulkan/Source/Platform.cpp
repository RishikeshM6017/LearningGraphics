#include "PCH.h"
#include "Platform.h"

GLFWwindow* Platform::BuildWindow(int width, int height, const char* appName)
{
	Logger* logger = Logger::GetLogger();

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(width, height, appName, NULL, NULL);

	if (window == NULL) { logger->Print("Failed to create window"); }
	else				{ logger->Print("Created window"); }

	return window;
}
