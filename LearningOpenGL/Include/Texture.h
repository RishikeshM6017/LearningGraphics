#pragma once

#include <glad/glad.h>
#include <STB/stb_image.h>

#include "Shader.h"

class Texture
{
public:
	Texture(const char* image, const char* textureType, GLuint slot);


	void Link(Shader &shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();


public:
	GLuint ID;
	const char* type;
	GLuint unit;

};

