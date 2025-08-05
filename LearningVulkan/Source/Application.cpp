#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::Initialize(const char* appName, GLFWwindow* window)
{
	m_renderer.Initialize(appName, window);
}

void Application::Render()
{

}
