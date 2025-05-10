#include "PCH.h"


#include "Logger.h"
#include "Platform.h"
#include "Engine.h"
#include "Application.h"


void SpawnRenderThread(GLFWwindow* window, std::atomic<bool>* done)
{
	Engine* engine = new Engine(window);

	while (!*done)
	{

	}

	delete engine;
}


int main()
{
	Logger* logger = Logger::GetLogger();
	logger->SetDebug(true);

	int width = 960, height = 540;
	GLFWwindow* window = Platform::BuildWindow(width, height, "Vulkan Application");

	std::atomic<bool> done = false;
	std::thread renderThread(SpawnRenderThread, window, &done);
	
	Application* app = new Application(window);

	done = true;
	renderThread.join();
	glfwTerminate();

	return 0;
}