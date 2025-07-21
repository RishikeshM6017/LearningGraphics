#include "PCH.h"

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

	const char* vertexShaderSource =
		"#version 460 core\n"
		"layout (location = 0) in vec3 inPosition;\n"
		"layout (location = 1) in vec3 inColor;\n"
		"out vec3 vertexColor;\n"
		"void main()\n" 
		"{\n" 
		"	gl_Position = vec4(inPosition.x, inPosition.y, inPosition.z, 1.0);\n"
		"	vertexColor = inColor;\n"
		"}\0";

	const char* fragmentShaderSource =
		"#version 460 core\n"
		"in vec3 vertexColor;\n"
		"out vec4 fragmentColor;\n"
		"void main() { fragmentColor = vec4(vertexColor, 1.0f); }\0";


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

	U32 vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	{
		I32 result;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			printf("ERROR::SHADER::VERTEX Compilation Failed\n %s\n", infoLog);
		}
	}

	U32 fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	{
		I32 result;
		char infoLog[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			printf("ERROR::SHADER::FRAGMENT Compilation Failed\n %s\n", infoLog);
		}
	}

	U32 shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	{
		I32 result;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			printf("ERROR::SHADER::PROGRAM Linking Failed\n %s\n", infoLog);
		}
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	F32 vertices[] = 
	{
		//VertexPositions		//VertexColors
		 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	//TopRight
		 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	//BottomRight
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	//BottomLeft
		-0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 0.0f	//TopLeft
	};

	U32 indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	U32 VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(F32), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(F32), (void*)(3 * sizeof(F32)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, ARRAY_SIZE(indices), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
}


