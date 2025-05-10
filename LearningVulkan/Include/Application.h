#pragma once

#include "PCH.h"

#include "Logger.h"

class Application
{
public:
	Application(GLFWwindow* window);

private:
	void MainLoop();

private:
	GLFWwindow* window;
	Logger* logger;
};

