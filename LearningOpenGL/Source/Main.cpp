
#include <iostream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>

#include "Shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"


const unsigned int window_width = 540;
const unsigned int window_height = 540;


void ResizeFramebuffer(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


float vertices[] = {
	 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,// top right
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,// bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,// bottom left
	-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f // top left 
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

int main()
{
	//GLFWInitialization
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//WindowCreation
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "LearningOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, ResizeFramebuffer);


	//GLADInitialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	

	//Vertex
	VAO vao = VAO();
	vao.Bind();

	VBO vbo = VBO(vertices, sizeof(vertices));
	EBO ebo = EBO(indices, sizeof(indices));

	vao.LinkAttribute(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
	vao.LinkAttribute(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	vao.LinkAttribute(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*) (6 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
	

	//ShaderCompilation
	Shader shader = Shader("Shaders/sample.vert", "Shaders/sample.frag");

	GLuint uniformID = glGetUniformLocation(shader.ID, "scale");


	//Textures
	stbi_set_flip_vertically_on_load(true);

	Texture texture = Texture("Textures/mario.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);	

	texture.Link(shader, "tex0", 0);


	//RenderLoop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		ProcessInput(window);


		//RenderCommands
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();
		glUniform1f(uniformID, 1.0f);
		glBindTexture(GL_TEXTURE_2D, texture.ID);
		vao.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0); // no need to unbind it every time 

		//SwapBuffers
		glfwSwapBuffers(window);


		//PollIOEvents
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	texture.Delete();
	shader.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}