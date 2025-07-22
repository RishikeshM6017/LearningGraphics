#pragma once

#include "PCH.h"

#include "Instance.h"
#include "Logger.h"

class Renderer
{
public:
	Renderer(Window window);
	~Renderer();

private:
	Logger* logger{ Logger::GetLogger() };

	Window window;

	Deque<Function<void()>> deletionQueue;

	vk::Instance instance;
};

