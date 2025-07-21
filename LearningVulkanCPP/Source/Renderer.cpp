#include "PCH.h"
#include "Renderer.h"

Renderer::Renderer(Window window) : window(window)
{
	logger = Logger::GetLogger();

	logger->Print("Renderer Started");
}

Renderer::~Renderer()
{
	logger->Print("Renderer Shutdown");
}


