#pragma once

#include "Renderer.h"

class Application
{
public:
	Application();
	~Application();

public:
	void Initialize(const char* appName, GLFWwindow* window);
	void Render();

private:
	Renderer m_renderer;
};

