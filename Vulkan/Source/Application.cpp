#include "Application.h"

#define VK_CHECK(x, msg) if (x != VK_SUCCESS) {throw std::runtime_error(msg);}

void Application::InitializeWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(windowWidth, windowHeight, appName, NULL, NULL);
}

void Application::InitializeVulkan()
{
	CreateVulkanInstance();
}

void Application::Update()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

void Application::Cleanup()
{

	vkDestroyInstance(instance, nullptr);

	glfwDestroyWindow(window);
	glfwTerminate();
}


void Application::CreateVulkanInstance()
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    //appInfo.pNext = nullptr;
    appInfo.pApplicationName = appName;
    appInfo.applicationVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
    appInfo.pEngineName = engineName;
    appInfo.engineVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

	std::vector<const char*> extensions = GetInstanceExtensions();

	QueryInstanceExtensionSupport();

	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    //instanceInfo.pNext = nullptr;
    //instanceInfo.flags = NULL;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledLayerCount = (uint32_t)layers.size();
    instanceInfo.ppEnabledLayerNames = layers.data();
    instanceInfo.enabledExtensionCount = (uint32_t)extensions.size();
    instanceInfo.ppEnabledExtensionNames = extensions.data();

	VkResult result = vkCreateInstance(&instanceInfo, nullptr, &instance);
	VK_CHECK(result, "Failed to create Instance")
}


std::vector<const char*> Application::GetInstanceExtensions()
{
	std::vector<const char*> extensions;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	for (uint32_t i = 0; i < glfwExtensionCount; i++)
	{
		extensions.emplace_back(glfwExtensions[i]);
	}

	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return extensions;
}

std::vector<const char*> Application::GetInstanceLayers()
{
	return layers;
}

void Application::QueryInstanceExtensionSupport()
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	std::cout << "Available Instance Extensions:\n";
	for (const auto& extension : extensions)
	{
		std::cout << '\t' << extension.extensionName << '\n';
	}
}