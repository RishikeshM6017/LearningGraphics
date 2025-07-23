#pragma once

#include "PCH.h"

class VBO
{
public:
	VBO(F32* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();

public:
	U32 ID;
};

