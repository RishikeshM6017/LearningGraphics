#include "PCH.h"

#include "Logger.h"
#include "Platform.h"
#include "Application.h"
#include "Renderer.h"

void SpawnRenderThread(Window window, Atomic<B8>* isDone)
{
	Renderer* renderer = new Renderer(window);

	while (!*isDone)
	{

	}

	delete renderer;
}

int main()
{
	Logger* logger = Logger::GetLogger();
	logger->SetMode(true);

	I32 width = 540, height = 540;

	Window window = Platform::BuildWindow(width, height, "VUlkan Application");

	Atomic<B8> isDone = false;

	Thread renderThread(SpawnRenderThread, window, &isDone);

	Application* app = new Application(window);

	isDone = true;
	renderThread.join();

	glfwTerminate();

	return 0;
}