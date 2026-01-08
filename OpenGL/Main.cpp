#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{

}

int main(int argc, char** argv)
{
	//Static Data
	int width = 960;
	int height = 540;

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	const char* vertexShaderCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 inPosition;\n"
		"void main()\n"
		"{ gl_Position = vec4(inPosition, 1.0) }";

	const char* fragmentShaderCode = 
		"#version 330 core\n"

	//GLFW Initialisation
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//Window Creation
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Application", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	//GLAD Initialisation Check
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	uint32_t VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);


	//Main Loop
	while (!glfwWindowShouldClose(window))
	{
		//Input Processing
		ProcessInput(window);

		//Rendering Commands
		glClear(GL_COLOR_BUFFER_BIT);

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;

}

