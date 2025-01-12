
#include <stdio.h>
#include <assert.h>
#include <vector>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>

#define ARRAY_SIZE(x)\
sizeof(x)/sizeof(x[0])

#define VK_CHECK(x, msg)	\
if (x != VK_SUCCESS)		\
{printf(msg);				\
assert(false);}			

#define VK_TEST(x)			\
if (x != VK_SUCCESS)		\
{assert(false);}	

// Check Validation Layer Support
//bool CheckValidationLayerSupport() 
//{
//	uint32_t layerCount;
//	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
//
//	std::vector<VkLayerProperties> availableLayers(layerCount);
//	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
//
//	for (const char* layerName : validationLayers) {
//		bool layerFound = false;
//
//		for (const auto& layerProperties : availableLayers) {
//			if (strcmp(layerName, layerProperties.layerName) == 0) {
//				layerFound = true;
//				break;
//			}
//		}
//
//		if (!layerFound) {
//			return false;
//		}
//	}
//
//	return true;
//}

//TODO: Check for layer and extension support
VkResult CreateVulkanInstance(VkInstance* pInstance)
{
	const char* layers[] =
	{
#ifdef _DEBUG
		"VK_LAYER_KHRONOS_validation"
#endif // ValidationLayers
	};

	const char* extensions[] =
	{
		VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef VK_USE_PLATFORM_WIN32_KHR
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#endif
	};

	//TODO: Check if Vulkan 1.3 is supported using vkEnumerateInstanceVersion
	VkApplicationInfo appInfo = {};
	appInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
	//appInfo.pNext				= nullptr;
	appInfo.pApplicationName	= "Vulkan Renderer";
	appInfo.applicationVersion	= VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName			= "Vulkan Engine";
	appInfo.engineVersion		= VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion			= VK_API_VERSION_1_3;

	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType						= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	//instanceInfo.pNext					= nullptr;
	//instanceInfo.flags					= 0;
	instanceInfo.pApplicationInfo			= &appInfo;
	instanceInfo.enabledLayerCount			= ARRAY_SIZE(layers);
	instanceInfo.ppEnabledLayerNames		= layers;
	instanceInfo.enabledExtensionCount		= ARRAY_SIZE(extensions);
	instanceInfo.ppEnabledExtensionNames	= extensions;

	return vkCreateInstance(&instanceInfo, nullptr, pInstance);
}

VkResult PickPhysicalDevice(VkInstance instance, VkPhysicalDevice* pPhysicalDevice)
{
	VkPhysicalDevice physicalDevices[16];
	uint32_t physicalDeviceCount = ARRAY_SIZE(physicalDevices);
	vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices);

	for (uint32_t i = 0; i < physicalDeviceCount; i++)
	{
		VkPhysicalDeviceProperties physicalDeviceProperties;
		vkGetPhysicalDeviceProperties(physicalDevices[i], &physicalDeviceProperties);

		if (physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			printf("Picking Discrete GPU: %s\n", physicalDeviceProperties.deviceName);
			*pPhysicalDevice = physicalDevices[i];
			return VK_SUCCESS;
		}
	}

	if (physicalDeviceCount > 0)
	{
		VkPhysicalDeviceProperties physicalDeviceProperties;
		vkGetPhysicalDeviceProperties(physicalDevices[0], &physicalDeviceProperties);
		printf("Picking fallback GPU: %s\n", physicalDeviceProperties.deviceName);
		*pPhysicalDevice = physicalDevices[0];
		return VK_SUCCESS;
	}

	return VK_ERROR_INITIALIZATION_FAILED;

}

//TODO: Queue Families
VkResult CreateVulkanDevice(VkPhysicalDevice physicalDevice, VkDevice* pDevice, uint32_t* pFamilyIndex)
{
	//TODO: Get this value from queue properties
	*pFamilyIndex = 0;

	//TODO: Needs to computed from queue properties
	uint32_t queueFamilyPropertyCount = 0;
	VkQueueFamilyProperties queueFamilyProperties;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, &queueFamilyProperties);

	float queuePriorities[] = { 1.0f };

	VkDeviceQueueCreateInfo deviceQueueInfo = {};
	deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueInfo.pNext = nullptr;
	deviceQueueInfo.flags = 0;
	deviceQueueInfo.queueFamilyIndex = *pFamilyIndex;
	deviceQueueInfo.queueCount = 1;
	deviceQueueInfo.pQueuePriorities = queuePriorities;

	VkDeviceQueueCreateInfo deviceQueueInfos[] =
	{
		deviceQueueInfo
	};

	const char* extensions[] =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	VkDeviceCreateInfo deviceInfo = {};
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.pNext = nullptr;
	deviceInfo.flags = 0;
	deviceInfo.queueCreateInfoCount		= ARRAY_SIZE(deviceQueueInfos);
	deviceInfo.pQueueCreateInfos		= deviceQueueInfos;
	//deviceInfo.enabledLayerCount		= ;
	//deviceInfo.ppEnabledLayerNames		= ;
	deviceInfo.enabledExtensionCount	= ARRAY_SIZE(extensions);
	deviceInfo.ppEnabledExtensionNames	= extensions;
	//deviceInfo.pEnabledFeatures			= ;

	return vkCreateDevice(physicalDevice, &deviceInfo, nullptr, pDevice);
}

VkResult CreateVulkanSurface(VkInstance instance, VkSurfaceKHR* pSurface, GLFWwindow* window)
{
#ifdef VK_USE_PLATFORM_WIN32_KHR

	VkWin32SurfaceCreateInfoKHR surfaceInfo = {};
	surfaceInfo.sType		= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceInfo.pNext		= nullptr;
	surfaceInfo.flags		= 0;
	surfaceInfo.hinstance	= GetModuleHandle(0);
	surfaceInfo.hwnd		= glfwGetWin32Window(window);

	return vkCreateWin32SurfaceKHR(instance, &surfaceInfo, nullptr, pSurface);

#else
#error INVALID_PLATFORM
#endif
}

//TODO: Query surface capabilities and create based on that
VkResult CreateVulkanSwapchain(VkDevice device, VkSurfaceKHR surface ,VkSwapchainKHR* pSwapchain, uint32_t* pFamilyIndex, GLFWwindow* window)
{
	int width = 0;
	int height = 0;
	glfwGetWindowSize(window, &width, &height);

	VkSwapchainCreateInfoKHR swapchainInfo = {};
	swapchainInfo.sType					= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainInfo.pNext					= nullptr;
	swapchainInfo.flags					= 0;
	swapchainInfo.surface				= surface;
	swapchainInfo.minImageCount			= 2;
	swapchainInfo.imageFormat			= VK_FORMAT_R8G8B8A8_UNORM;	//TODO: Make Dynamic based on device support
	swapchainInfo.imageColorSpace		= VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	swapchainInfo.imageExtent.width		= width;
	swapchainInfo.imageExtent.height	= height;
	swapchainInfo.imageArrayLayers		= 1;
	swapchainInfo.imageUsage			= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	//swapchainInfo.imageSharingMode		= ;
	swapchainInfo.queueFamilyIndexCount = 1;
	swapchainInfo.pQueueFamilyIndices	= pFamilyIndex;
	swapchainInfo.preTransform			= VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	swapchainInfo.compositeAlpha		= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainInfo.presentMode			= VK_PRESENT_MODE_FIFO_KHR;
	//swapchainInfo.clipped;
	//swapchainInfo.oldSwapchain;

	return vkCreateSwapchainKHR(device, &swapchainInfo, nullptr, pSwapchain);
}

VkResult CreateVulkanSemaphore(VkDevice device, VkSemaphore* pSemaphore)
{
	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semaphoreInfo.pNext = nullptr;
	semaphoreInfo.flags = 0;

	return vkCreateSemaphore(device, &semaphoreInfo, nullptr, pSemaphore);
}

VkResult CreateVulkanCommandPool(VkDevice device, uint32_t queueFamilyIndex, VkCommandPool* pCommandPool)
{
	VkCommandPoolCreateInfo commandPoolInfo = {};
	commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolInfo.pNext = nullptr;
	commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	commandPoolInfo.queueFamilyIndex = queueFamilyIndex;

	return vkCreateCommandPool(device, &commandPoolInfo, nullptr, pCommandPool);
}

int main()
{
	VkInstance			instance		= 0;
	VkPhysicalDevice	physicalDevice	= 0;
	VkDevice			device			= 0;
	VkSurfaceKHR		surface			= 0;
	VkSwapchainKHR		swapchain		= 0;
	VkSemaphore			acquireSemaphore= 0;
	VkSemaphore			releaseSemaphore= 0;
	VkQueue				queue			= 0;
	VkCommandPool		commandPool		= 0;
	VkCommandBuffer		commandBuffer	= 0;

	uint32_t familyIndex = 0;

	VK_CHECK(CreateVulkanInstance(&instance),							"Failed to create instance");

	VK_CHECK(PickPhysicalDevice(instance, &physicalDevice),				"Failed to find suitable GPU");

	VK_CHECK(CreateVulkanDevice(physicalDevice, &device, &familyIndex), "Failed to create device");

	int result = glfwInit();
	assert(result == GLFW_TRUE);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(960, 540, "Vulkan Renderer", 0, 0);
	assert(window);

	VK_CHECK(CreateVulkanSurface(instance, &surface, window),							"Failed to create surface");

	VK_CHECK(CreateVulkanSwapchain(device, surface, &swapchain, &familyIndex, window),	"Failed to create swapchain");

	VK_CHECK(CreateVulkanSemaphore(device, &acquireSemaphore),							"Failed to create semaphore");

	VK_CHECK(CreateVulkanSemaphore(device, &releaseSemaphore),							"Failed to create semaphore")

	vkGetDeviceQueue(device, familyIndex, 0, &queue);

	VkImage swapchainImages[16]; //SHORTCUT
	uint32_t swapchainImageCount = ARRAY_SIZE(swapchainImages);
	VK_TEST(vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, swapchainImages));

	VK_CHECK(CreateVulkanCommandPool(device, familyIndex, &commandPool), "failed to create command pool");

	VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
	commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocateInfo.pNext = nullptr;
	commandBufferAllocateInfo.commandPool = commandPool;
	commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferAllocateInfo.commandBufferCount = 1;
	VK_CHECK(vkAllocateCommandBuffers(device, &commandBufferAllocateInfo, &commandBuffer), "Failed to allocate command buffers");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		uint32_t imageIndex = 0;
		VK_TEST(vkAcquireNextImageKHR(device, swapchain, ~0ull, acquireSemaphore, VK_NULL_HANDLE, &imageIndex));

		VK_TEST(vkResetCommandPool(device, commandPool, 0));

		/*VkCommandBufferInheritanceInfo commandBufferInheritanceInfo = {};
		commandBufferInheritanceInfo.sType	= VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
		commandBufferInheritanceInfo.pNext	= nullptr;
		commandBufferInheritanceInfo.renderPass;
		commandBufferInheritanceInfo.subpass;
		commandBufferInheritanceInfo.framebuffer;
		commandBufferInheritanceInfo.occlusionQueryEnable;
		commandBufferInheritanceInfo.queryFlags;
		commandBufferInheritanceInfo.pipelineStatistics;*/

		VkCommandBufferBeginInfo commandBufferBeginInfo = {};
		commandBufferBeginInfo.sType	= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		commandBufferBeginInfo.pNext	= nullptr;
		commandBufferBeginInfo.flags	= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		//commandBufferBeginInfo.pInheritanceInfo = &commandBufferInheritanceInfo;

		VK_TEST(vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo));

		VkClearColorValue clearColor = { 1, 0, 1, 1 };
		VkImageSubresourceRange range = {};
		range.aspectMask		= VK_IMAGE_ASPECT_COLOR_BIT;
		//range.baseMipLevel		= 1;
		range.levelCount		= 1;
		//range.baseArrayLayer	= 1;
		range.layerCount		= 1;
		vkCmdClearColorImage(commandBuffer, swapchainImages[imageIndex], VK_IMAGE_LAYOUT_GENERAL, &clearColor, 1, &range);

		VK_TEST(vkEndCommandBuffer(commandBuffer));

		VkPipelineStageFlags submitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pNext = nullptr;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &acquireSemaphore;
		submitInfo.pWaitDstStageMask = &submitStageMask;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &releaseSemaphore;
		VK_TEST(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE));

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.pNext = nullptr;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &releaseSemaphore;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &swapchain;
		presentInfo.pImageIndices = &imageIndex;
		//presentInfo.pResults = ;

		VK_TEST(vkQueuePresentKHR(queue, &presentInfo));

		VK_TEST(vkDeviceWaitIdle(device));
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	
	vkDestroySwapchainKHR(device, swapchain, nullptr);
	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyDevice(device, nullptr);
	vkDestroyInstance(instance, nullptr);

	return 0;
}