#include "Texture.h"

Texture::Texture(const char* imagePath, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = textureType;

	int imgWidth, imgHeight, imgChannels;

	unsigned char* bytes = stbi_load(imagePath, &imgWidth, &imgHeight, &imgChannels, 0);

	glGenTextures(1, &ID);

	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(textureType, 0, GL_RGBA, imgWidth, imgHeight, 0, format, pixelType, bytes);

	glGenerateMipmap(textureType);

	stbi_image_free(bytes);

	glBindTexture(textureType, 0);
}

void Texture::Link(Shader shader, const char* uniform, GLuint unit)
{
	GLuint textureUniform = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(textureUniform, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
