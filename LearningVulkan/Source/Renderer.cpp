#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	printf("Shutting Down...\n");

	vkDestroySurfaceKHR(m_instance, m_surface, NULL);

	PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessenger = VK_NULL_HANDLE;
	vkDestroyDebugUtilsMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT");
	if (!vkDestroyDebugUtilsMessenger)
	{
		printf("Could not find address of vkDestroyDebugUtilsMessenger\n");
		exit(-1);
	}
	vkDestroyDebugUtilsMessenger(m_instance, m_debugMessenger, NULL);
	printf("Debug messenger destroyed\n");

	vkDestroyInstance(m_instance, NULL);
	printf("Vulkan instance destroyed\n");
}


void Renderer::Initialize(const char* appName, GLFWwindow* window)
{
	CreateInstance(appName);
	CreateDebugMessenger();
	CreateSurface(window);
}


void Renderer::CreateInstance(const char* appName)
{
	uint32_t version = 0;

	vkEnumerateInstanceVersion(&version);
	version &= ~0xFFFU;

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = NULL;
    appInfo.pApplicationName = appName;
    appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
    appInfo.pEngineName = "Vulkan Engine";
    appInfo.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
    appInfo.apiVersion = version;

	std::vector<const char*> layers =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	std::vector<const char*> extensions =
	{
		VK_KHR_SURFACE_EXTENSION_NAME,
		"VK_KHR_win32_surface",
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME
	};
	
	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pNext = NULL;
    instanceInfo.flags = 0;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledLayerCount = (uint32_t)layers.size();
    instanceInfo.ppEnabledLayerNames = layers.data();
    instanceInfo.enabledExtensionCount = (uint32_t)extensions.size();
    instanceInfo.ppEnabledExtensionNames = extensions.data();

	VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &m_instance), "create instance");

	printf("Created Vulkan Instance\n");
}


static const char* GetDebugSeverityString(VkDebugUtilsMessageSeverityFlagBitsEXT severity)
{
	switch (severity)
	{
		case (VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT):
		{
			return "VERBOSE";
		}
		case (VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT):
		{
			return "INFO";
		}
		case (VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT):
		{
			return "WARNING";
		}
		case (VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT):
		{
			return "ERROR";
		}
		default:
		{
			//TODO: Logging
			printf("Invalid severity %d\n", severity);
			exit(-1);
		}
	}
}

static const char* GetDebugTypeString(VkDebugUtilsMessageTypeFlagsEXT type)
{
	static char buffer[128];
	buffer[0] = '\0';

	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
	{
		strcat_s(buffer, sizeof(buffer), "GENERAL\t");
	}
	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
	{
		strcat_s(buffer, sizeof(buffer), "VALIDATION\t");
	}
	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
	{
		strcat_s(buffer, sizeof(buffer), "PERFORMANCE\t");
	}
	if (type & VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT)
	{
		strcat_s(buffer, sizeof(buffer), "DEVICE ACCESS BINDING");
	}

	if (buffer[0] == '\0') {
		return "UNKNOWN";
	}

	return buffer;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT severity,
	VkDebugUtilsMessageTypeFlagsEXT type,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	printf("Debug Callback: %s\n", pCallbackData->pMessage);
	printf("\tSeverity: %s\n", GetDebugSeverityString(severity));
	printf("\tType: %s\n", GetDebugTypeString(type));
	printf("\tObjects: \n");

	for (uint32_t i = 0; i < pCallbackData->objectCount; i++)
	{
		printf("\t\t%llx \n", pCallbackData->pObjects[i].objectHandle);
	}

	return VK_FALSE;
}

void Renderer::CreateDebugMessenger()
{
	VkDebugUtilsMessengerCreateInfoEXT messengerInfo = {};
	messengerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    messengerInfo.pNext = nullptr;
    messengerInfo.flags = 0;
    messengerInfo.messageSeverity = 
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | 
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    messengerInfo.messageType = 
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    messengerInfo.pfnUserCallback = &DebugCallback;
    messengerInfo.pUserData = NULL;

	PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessenger = VK_NULL_HANDLE;
	vkCreateDebugUtilsMessenger = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");
	if (!vkCreateDebugUtilsMessenger)
	{
		//TODO: Log Error
		printf("Could not find address of vkCreateDebugUtilsMessengerEXT\n");
		exit(-1);
	}

	VK_CHECK(vkCreateDebugUtilsMessenger(m_instance, &messengerInfo, NULL, &m_debugMessenger), "Failed to create debug messenger");

	printf("Created Debug Messenger\n");
}

void Renderer::CreateSurface(GLFWwindow* window)
{
	VK_CHECK(glfwCreateWindowSurface(m_instance, window, NULL, &m_surface), "Failed to create surface");
	
	printf("Created window surface\n");
}