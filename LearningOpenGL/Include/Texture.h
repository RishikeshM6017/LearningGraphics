#pragma once

#include <glad/glad.h>
#include <STB/stb_image.h>

#include "Shader.h"

class Texture
{
public:
	Texture(const char* image, GLenum textureType, GLuint slot, GLenum format, GLenum pixelType);


	void Link(Shader &shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();


public:
	GLuint ID;
	GLenum type;
	GLuint unit;

};

