#include "PCH.h"
#include "Engine.h"

Engine::Engine(GLFWwindow* window) :window(window)
{
	logger = Logger::GetLogger();
	logger->Print("Initialized Graphics Engine");
}

Engine::~Engine()
{
}
