#include "PCH.h"
#include "Application.h"

Application::Application(GLFWwindow* window) : window(window)
{
	logger = Logger::GetLogger();

	MainLoop();
}

void Application::MainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	logger->Print("Application Closed");
}
