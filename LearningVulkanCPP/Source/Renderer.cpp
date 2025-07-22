#include "PCH.h"
#include "Renderer.h"

Renderer::Renderer(Window window) : window(window)
{
	logger = Logger::GetLogger();

	instance = BuildInstance("Vulkan Engine", deletionQueue);

	logger->Print("Renderer Started");
}

Renderer::~Renderer()
{
	logger->Print("Renderer Shutdown");

	while (deletionQueue.size() > 0)
	{
		deletionQueue.back()();
		deletionQueue.pop_back();
	}
}


