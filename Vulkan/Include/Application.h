#pragma once

#define GLFW_INCLUDE_VULKAN

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include <GLFW/glfw3.h>

class Application
{
public:
	void Run()
	{
		InitializeWindow();
		InitializeVulkan();
		Update();
		Cleanup();
	}

private:
	void InitializeWindow();
	void InitializeVulkan();
	void Update();
	void Cleanup();

	void CreateVulkanInstance();

	std::vector<const char*> GetInstanceExtensions();
	std::vector<const char*> GetInstanceLayers();

	void QueryInstanceExtensionSupport();

public:
	const uint32_t windowWidth = 960;
	const uint32_t windowHeight = 540;

	const char* appName = "Vulkan Application";
	const char* engineName = "Vulkan Engine";

	std::vector<const char*> layers =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	GLFWwindow* window = NULL;

	VkInstance instance = VK_NULL_HANDLE;

};

