#pragma once

#include "PCH.h"

class Renderer
{
public:
	Renderer(GLFWwindow* window);
	~Renderer();

public:
	void Initialize(GLFWwindow* window);
	void Update();
	void Render();
	void Present();
	void Shutdown();

private:
	VkInstance		 instance		= VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice		 device			= VK_NULL_HANDLE;



	VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkQueue presentQueue  = VK_NULL_HANDLE;
	//VkQueue computeQueue;

	VkSwapchainKHR swapchain = VK_NULL_HANDLE;

	Vector<VkImage>		images;
	Vector<VkImageView> imageViews;


};

