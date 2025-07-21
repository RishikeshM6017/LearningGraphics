#include "PCH.h"

#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	U32 vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	String vertexShaderCode = Platform::ReadFileToString(vertexShaderPath);
	const char* vertexShaderSource = vertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	CheckCompilation(vertexShader);

	U32 fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	String fragmentShaderCode = Platform::ReadFileToString(fragmentShaderPath);
	const char* fragmentShaderSource = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	CheckCompilation(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	CheckLinking(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::CheckCompilation(U32 shader)
{
	I32 result;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("ERROR::SHADER Compilation Failed\n %s\n", infoLog);
	}
}

void Shader::CheckLinking(U32 program)
{
	I32 result;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("ERROR::SHADERPROGRAM Linking Failed\n %s\n", infoLog);
	}
}
