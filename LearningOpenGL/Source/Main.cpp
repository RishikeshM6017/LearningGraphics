#include "PCH.h"

#include "Shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

void OnWindowResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	
}

int main()
{
	const I32 windowWidth = 540;
	const I32 windowHeight = 540;

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Application", NULL, NULL);

	if (window == NULL)
	{
		printf("Failed to create a window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, OnWindowResize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	Shader shader = Shader("Resources/Shaders/sample.vert", "Resources/Shaders/sample.frag");

	F32 vertices[] = 
	{
		//VertexPositions		//VertexColors
		 0.5f,  0.5f, 0.0f,		//1.0f, 0.0f, 0.0f,	//TopRight
		 0.5f, -0.5f, 0.0f,		//0.0f, 1.0f, 0.0f,	//BottomRight
		-0.5f, -0.5f, 0.0f,		//0.0f, 0.0f, 1.0f,	//BottomLeft
		-0.5f,  0.5f, 0.0f,		//0.0f, 0.0f, 0.0f	//TopLeft
	};

	U32 indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	
	VAO vao;
	vao.Bind();

	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkVBO(vbo, 0);

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, ARRAY_SIZE(indices), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shader.Delete();

	glfwTerminate();

	return 0;
}


