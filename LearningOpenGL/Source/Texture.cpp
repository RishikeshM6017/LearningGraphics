#include "Texture.h"

Texture::Texture(const char* imagePath, const char* textureType, GLuint slot, GLenum format, GLenum pixelType)
{
	type = textureType;
	unit = slot;

	int imgWidth, imgHeight, imgChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(imagePath, &imgWidth, &imgHeight, &imgChannels, 0);

	glGenTextures(1, &ID);

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, format, pixelType, bytes);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);

	glBindTexture(GL_TEXTURE_2D, 0);
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
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
