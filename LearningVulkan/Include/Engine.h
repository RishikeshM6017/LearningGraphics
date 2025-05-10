#pragma once

#include "PCH.h"
#include "Logger.h"

class Engine
{
public:
	Engine(GLFWwindow* window);
	~Engine();

public:
	GLFWwindow* window;
	Logger* logger;
};

