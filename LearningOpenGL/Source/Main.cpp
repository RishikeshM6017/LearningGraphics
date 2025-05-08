
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
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

GLuint meshIndices[] =
{
	0, 1, 2,
	0, 2, 3
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
	

	//Mesh
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


	//Light
	Shader lightShader("Shaders/light.vert", "Shaders/light.frag");
	
	VAO lightVAO = VAO();
	lightVAO.Bind();

	VBO lightVBO = VBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO = EBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttribute(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*) 0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos	 = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 meshPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 meshModel = glm::mat4(1.0f);
	meshModel = glm::translate(meshModel, meshPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	meshShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(meshShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(meshModel));
	glUniform4f(glGetUniformLocation(meshShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(meshShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	//Textures
	stbi_set_flip_vertically_on_load(true);

	Texture albedoTexture = Texture("Textures/planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);	
	albedoTexture.Link(meshShader, "albedoTex", 0);

	Texture specularTexture = Texture("Textures/planks_specular.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	specularTexture.Link(meshShader, "specularTex", 1);


	//Camera
	Camera camera = Camera(window_width, window_height, glm::vec3(0.0f, 0.0f, 2.0f));


	glEnable(GL_DEPTH_TEST);

	//RenderLoop
	while (!glfwWindowShouldClose(window))
	{
		//Input
		ProcessInput(window);
		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);


		//RenderCommands
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//DrawMesh
		meshShader.Activate();
		glUniform3f(glGetUniformLocation(meshShader.ID, "cameraPos"), camera.position.x, camera.position.y, camera.position.z);
		camera.Link(meshShader, "camera");
		albedoTexture.Bind();
		specularTexture.Bind();
		meshVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(meshIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		//DrawLight
		lightShader.Activate();
		camera.Link(lightShader, "camera");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


		//SwapBuffers
		glfwSwapBuffers(window);


		//PollIOEvents
		glfwPollEvents();
	}

	meshVAO.Delete();
	meshVBO.Delete();
	meshEBO.Delete();
	albedoTexture.Delete();
	specularTexture.Delete();
	meshShader.Delete();

	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}