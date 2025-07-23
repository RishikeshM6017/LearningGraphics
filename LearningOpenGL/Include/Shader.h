#pragma once

#include "PCH.h"

#include "Platform.h"

class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void Activate();
	void Delete();

	void CheckCompilation(U32 shader);
	void CheckLinking(U32 program);

public:
	U32 ID;
};

