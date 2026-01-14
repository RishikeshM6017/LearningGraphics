#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"


const uint32_t screenWidth = 960;
const uint32_t screenHeight = 540;

float vertices[] = 
{
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};
unsigned int indices[] =
{
	0, 1, 2
};


void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{

}


int main()
{
	GLFWwindow* window = NULL;
	uint32_t shaderProgram = NULL;
	uint32_t VBO, VAO, EBO;


	//GLFW Initialization
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Application", NULL, NULL);

		if (window == NULL)
		{
			std::cout << "Failed to create window" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	}


	//GLAD Initialization
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
	}


	//Shader Initialization
	Shader shader = Shader("Resources/Shader.vs", "Resources/Shader.fs");


	//Mesh Initialisation
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);


	//Main Loop
	{
		while (!glfwWindowShouldClose(window))
		{
			ProcessInput(window);

			//Render
			{
				glClear(GL_COLOR_BUFFER_BIT);

				shader.Use();

				glBindVertexArray(VAO);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				glBindVertexArray(0);
			}

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}


	//Shutdown
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteProgram(shaderProgram);

		glfwTerminate();
	}


	return 0;
}
