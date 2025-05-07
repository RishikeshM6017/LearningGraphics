
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
#include "Camera.h"


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


GLfloat meshVertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

GLuint meshIndices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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
	Shader meshShader = Shader("Shaders/sample.vert", "Shaders/sample.frag");
	
	VAO meshVAO = VAO();
	meshVAO.Bind();

	VBO meshVBO = VBO(meshVertices, sizeof(meshVertices));
	EBO meshEBO = EBO(meshIndices, sizeof(meshIndices));

	meshVAO.LinkAttribute(meshVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*) 0);
	meshVAO.LinkAttribute(meshVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*) (3 * sizeof(float)));
	meshVAO.LinkAttribute(meshVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*) (6 * sizeof(float)));
	meshVAO.LinkAttribute(meshVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*) (8 * sizeof(float)));

	meshVAO.Unbind();
	meshVBO.Unbind();
	meshEBO.Unbind();
	

	Shader lightShader("Shaders/light.vert", "Shaders/light.frag");
	
	VAO lightVAO = VAO();
	lightVAO.Bind();

	VBO lightVBO = VBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO = EBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttribute(meshVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*) 0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();



	//Textures
	stbi_set_flip_vertically_on_load(true);

	Texture texture = Texture("Textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);	
	texture.Link(meshShader, "tex0", 0);


	glEnable(GL_DEPTH_TEST);


	Camera camera = Camera(window_width, window_height, glm::vec3(0.0f, 0.0f, 2.0f));

	//RenderLoop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		ProcessInput(window);
		camera.Inputs(window);

		//RenderCommands
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		meshShader.Activate();
		
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		
		camera.Link(meshShader, "camera");

		texture.Bind();
		
		meshVAO.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(meshIndices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

		//SwapBuffers
		glfwSwapBuffers(window);


		//PollIOEvents
		glfwPollEvents();
	}

	meshVAO.Delete();
	meshVBO.Delete();
	meshEBO.Delete();
	texture.Delete();
	meshShader.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}