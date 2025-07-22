#pragma once

#include "PCH.h"

class EBO
{
public:
	EBO(U32* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();

public:
	U32 ID;

};

