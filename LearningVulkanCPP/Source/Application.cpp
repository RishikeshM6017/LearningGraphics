#include "PCH.h"
#include "Application.h"

Application::Application(Window window) : window(window)
{
	logger = Logger::GetLogger();

	Run();
}

void Application::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	logger->Print("Window Closed");
}
