#pragma once

#include <vector>
#include <GLAD/glad.h>

class EBO
{
public:
	EBO(std::vector<GLuint> &indices);

public:
	void Bind();
	void Unbind();
	void Delete();

public:
	GLuint ID;
};

