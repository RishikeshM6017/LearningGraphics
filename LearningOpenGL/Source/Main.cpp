
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
#include "Mesh.h"


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


Vertex meshVertices[] =
{ //COORDINATES							  COLORS					   NORMALS						UV
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

GLuint meshIndices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //COORDINATES
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f,  0.1f,  0.1f)}
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
	

	//Textures
	Texture meshTextures[] =
	{
		Texture("Textures/planks.png",			"albedo",	0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("Textures/planks_specular.png", "specular", 1, GL_RED,	GL_UNSIGNED_BYTE)
	};


	//MeshShader
	Shader meshShader = Shader("Shaders/sample.vert", "Shaders/sample.frag");
	

	//Mesh
	std::vector<Vertex>  vertices(meshVertices, meshVertices + sizeof(meshVertices) / sizeof(Vertex));
	std::vector<GLuint>  indices (meshIndices,  meshIndices  + sizeof(meshIndices)  / sizeof(GLuint));
	std::vector<Texture> textures(meshTextures, meshTextures + sizeof(meshTextures) / sizeof(Texture));

	Mesh mesh(vertices, indices, textures);


	//LightShader
	Shader lightShader("Shaders/light.vert", "Shaders/light.frag");
	

	//Light
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInd  (lightIndices,  lightIndices  + sizeof(lightIndices)  / sizeof(GLuint));

	Mesh light(lightVerts, lightInd, textures);


	//StaticUniforms
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
		mesh.Draw(meshShader, camera);


		//DrawLight
		light.Draw(lightShader, camera);


		//SwapBuffers
		glfwSwapBuffers(window);


		//PollIOEvents
		glfwPollEvents();
	}


	meshShader.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}