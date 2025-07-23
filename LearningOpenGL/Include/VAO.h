#pragma once

#include "PCH.h"
#include "VBO.h"

class VAO
{
public:
	VAO();

	void LinkVBO(VBO vbo, U32 layout);

	void Bind();
	void Unbind();
	void Delete();

public:
	U32 ID;

};

