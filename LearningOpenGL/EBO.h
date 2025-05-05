#pragma once

#include <GLAD/glad.h>

class EBO
{
public:
	EBO(GLuint* indices, GLsizeiptr size);

public:
	void Bind();
	void Unbind();
	void Delete();

public:
	GLuint ID;
};

