#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>


class Shader
{
public:
	Shader(const char* vertexShaderSource, const char* fragmentShaderSource);

public:
	void Use();

	void SetBool (const std::string &name, bool  value) const;
	void SetInt  (const std::string &name, int   value) const;
	void SetFloat(const std::string &name, float value) const;

public:
	uint32_t ID;
};

