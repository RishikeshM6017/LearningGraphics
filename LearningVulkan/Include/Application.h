#pragma once

#include "PCH.h"

#include "VkUtility.h"
#include "Renderer.h"

class Application
{
public:
	Application();
	~Application();

public:
	void Initialize();
	void Run();
	void Shutdown();

private:
	//Renderer*   renderer = NULL;
	GLFWwindow* window   = NULL;

	const int window_width  = 540;
	const int window_height = 540;

	//TODO: Move logic and members to Renderer
	VkInstance		 instance		= VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice		 device			= VK_NULL_HANDLE;
	VkSurfaceKHR	 surface		= VK_NULL_HANDLE;
};

