#pragma once

#include "PCH.h"

#include "Logger.h"

class Renderer
{
public:
	Renderer(Window window);
	~Renderer();

private:
	Logger* logger{ Logger::GetLogger() };

	Window window;
};

