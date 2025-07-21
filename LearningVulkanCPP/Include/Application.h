#pragma once

#include "PCH.h"

#include "Logger.h"

class Application
{
public:
	Application(Window window);
	//~Application();

	void Run();

private:
	Window window;
	Logger* logger;
};

