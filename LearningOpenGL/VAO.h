#pragma once

#include "VBO.h"

class VAO
{
public:
	VAO();

public:
	void LinkAttribute(VBO& vbo, GLuint layout, GLuint componentCount, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();

public:
	GLuint ID;
};

