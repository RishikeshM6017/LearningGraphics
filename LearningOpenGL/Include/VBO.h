#pragma once

#include <GLAD/glad.h>

class VBO
{
public:
	VBO(GLfloat* vertices, GLsizeiptr size);

public:
	void Bind();
	void Unbind();
	void Delete();

public:
	unsigned int ID;
};

