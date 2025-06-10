#pragma once

#include "PCH.h"

namespace Vulkan
{
	struct QueueFamilyIndices
	{
		Optional<int> graphicsFamily;
		Optional<int> presentFamily;

		bool IsComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
	};

	VkResult CreateInstance(VkApplicationInfo* pAppInfo, Vector<const char*> layers, Vector<const char*> extensions, VkInstance* pInstance);
	
	VkResult PickPhysicalDevice(VkInstance instance, VkPhysicalDevice* pPhysicalDevice);

	VkResult CreateDevice(VkDevice* pDevice);

	VkResult CreateSwapchain(VkSwapchainKHR* pSwapchain);

	VkResult CreateImages(VkImage* pImages);

	VkResult CreateImageViews(VkImageView* pImageViews);

	VkResult CreateQueue(VkQueue* pQueue, VkDeviceQueueCreateInfo* pQueueInfo);

	VkResult CreateGraphicsQueue();

	VkResult CreatePresentQueue();

	VkResult CreateComputeQueue();


	Vector<const char*> GetRequiredInstanceExtensions();
	
	Vector<const char*> GetRequiredInstanceLayers();
}

