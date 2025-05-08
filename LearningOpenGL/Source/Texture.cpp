#include "Texture.h"

Texture::Texture(const char* imagePath, GLenum textureType, GLuint slot, GLenum format, GLenum pixelType)
{
	type = textureType;
	unit = slot;

	int imgWidth, imgHeight, imgChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(imagePath, &imgWidth, &imgHeight, &imgChannels, 0);

	glGenTextures(1, &ID);

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(textureType, ID);

	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(textureType, 0, GL_RGBA, imgWidth, imgHeight, 0, format, pixelType, bytes);

	glGenerateMipmap(textureType);

	stbi_image_free(bytes);

	glBindTexture(textureType, 0);
}

void Texture::Link(Shader &shader, const char* uniform, GLuint unit)
{
	GLuint textureUniform = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(textureUniform, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
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
