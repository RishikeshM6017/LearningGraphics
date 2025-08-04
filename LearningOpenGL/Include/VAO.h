#pragma once

#include "PCH.h"
#include "VBO.h"

class VAO
{
public:
	VAO();

	void LinkAttribute(VBO vbo, U32 layout, U32 componentCount, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void Unbind();
	void Delete();

public:
	U32 ID;

};

