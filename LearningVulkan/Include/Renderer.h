#pragma once

#define GLFW_INCLUDE_VULKAN

#include <vector>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#define VK_CHECK(x, msg)\
if (x != VK_SUCCESS)	\
{	fprintf(stderr, "Error in %s:%d - %s, code %x\n", __FILE__, __LINE__, msg, x); \
	exit(-1);\
}

class Renderer
{
public:
	Renderer();
	~Renderer();

public:
	void Initialize(const char* appName, GLFWwindow* window);

private:
	void CreateInstance(const char* appName);
	void CreateDebugMessenger();
	void CreateSurface(GLFWwindow* window);

private:
	VkInstance m_instance = VK_NULL_HANDLE;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;

	VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;
};

