#pragma once

#include "PCH.h"
#include "Logger.h"

namespace Platform
{
	//void InitializeGLFW();

	GLFWwindow* BuildWindow(int width, int height, const char* appName);
};

