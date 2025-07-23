#include "PCH.h"
#include "Instance.h"

vk::Instance BuildInstance(const char* engineName, Deque<Function<void()>>& deletionQueue)
{
	Logger* logger = Logger::GetLogger();

	U32 version = vk::enumerateInstanceVersion().value;
	version &= ~(0xFFFU);

	vk::ApplicationInfo appInfo = 
		vk::ApplicationInfo(
			"Vulkan Applicatio", 
			VK_MAKE_API_VERSION(1, 0, 0, 0), 
			engineName, 
			VK_MAKE_API_VERSION(1, 0, 0, 0), 
			version);

	U32 glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	//Vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
	//Vector<const char*> layers;

	logger->Print("Extensions:");
	logger->PrintList(glfwExtensions, glfwExtensionCount);

	vk::InstanceCreateInfo instanceInfo = 
		vk::InstanceCreateInfo(
			vk::InstanceCreateFlags(),
			&appInfo,
			0,
			nullptr,
			glfwExtensionCount,
			glfwExtensions
		);

	vk::ResultValue<vk::Instance> attempt = vk::createInstance(instanceInfo);

	if (attempt.result != vk::Result::eSuccess)
	{
		logger->Print("Failed to create instance");
		return nullptr;
	}

	vk::Instance instance = attempt.value;
	VkInstance handle = instance;

	deletionQueue.push_back([logger, handle]()
		{
			vkDestroyInstance(handle, nullptr);
			logger->Print("Deleted instance");
		});

	logger->Print("Instance created");

	return instance;
}
