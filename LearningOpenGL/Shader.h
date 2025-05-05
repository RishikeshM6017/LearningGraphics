#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include <GLAD/glad.h>

std::string LoadFromFile(const char* filename);

class Shader
{
public:
	Shader(const char* vertexShaderFile, const char* fragmentShaderFile);

public:
	void Activate();
	void Delete();
	void CheckCompilation(GLuint shader, const char type);

public:
	unsigned int ID;
};

