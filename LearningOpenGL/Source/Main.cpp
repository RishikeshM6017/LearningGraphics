
#include <iostream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

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


GLfloat vertices[] =
{   
	//COORDINATES			COLORS					TexCoord
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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


	//Textures
	stbi_set_flip_vertically_on_load(true);

	Texture texture = Texture("Textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);	

	texture.Link(shader, "tex0", 0);

	GLfloat rotation = 0.0f;

	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	//RenderLoop
	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();

		if (currentTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = currentTime;
		}

		//Input
		ProcessInput(window);


		//RenderCommands
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Activate();

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 viewMatrix  = glm::mat4(1.0f);
		glm::mat4 projMatrix  = glm::mat4(1.0f);

		GLuint modelLocation = glGetUniformLocation(shader.ID, "model");
		GLuint viewLocation  = glGetUniformLocation(shader.ID, "view");
		GLuint projLocation  = glGetUniformLocation(shader.ID, "proj");

		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -0.5f, -2.0f));
		projMatrix = glm::perspective(glm::radians(45.0f), float(window_width / window_height), 0.1f, 100.0f);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewLocation,  1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projLocation,  1, GL_FALSE, glm::value_ptr(projMatrix));
;
		glBindTexture(GL_TEXTURE_2D, texture.ID);

		vao.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

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