#include "PCH.h"
#include "Application.h"

void GLFWKEyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

Application::Application()
{
	Application::Initialize();
}

Application::~Application()
{
	Application::Shutdown();
}

void Application::Initialize()
{
	assert(glfwInit() == GLFW_TRUE);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE,  GLFW_FALSE);

	window = glfwCreateWindow(window_width, window_height, "Vulkan Application", NULL, NULL);
	assert(window != NULL);

	assert(glfwVulkanSupported() == GL_TRUE);
	
	//renderer = new Renderer();

	U32 version = 0;
	VK_TEST(vkEnumerateInstanceVersion(&version));
	version &= 0xFFU;

	VkApplicationInfo appInfo = {};
	appInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext				= nullptr;
    appInfo.pApplicationName	= "Vulkan Application";
    appInfo.applicationVersion	= VK_MAKE_API_VERSION(0, 1, 0, 0);
    appInfo.pEngineName			= "Vulkan Engine";
    appInfo.engineVersion		= VK_MAKE_API_VERSION(0, 1, 0, 0);
    appInfo.apiVersion			= version;

	Vector<const char*> extensions  = Vulkan::GetRequiredInstanceExtensions();
	Vector<const char*> layers		= Vulkan::GetRequiredInstanceLayers();

	VK_TEST(Vulkan::CreateInstance(&appInfo, extensions, layers, &instance));

	VK_TEST(glfwCreateWindowSurface(instance, window, nullptr, &surface));

	VK_TEST(Vulkan::PickPhysicalDevice(instance, &physicalDevice));


}

void Application::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

void Application::Shutdown()
{
	//delete renderer;

	glfwDestroyWindow(window);
	glfwTerminate();
}
