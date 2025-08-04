#include "PCH.h"

#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttribute(VBO vbo, U32 layout, U32 componentCount, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();

	glVertexAttribPointer(layout, componentCount, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(F32), (void*)(3 * sizeof(F32)));
	//glEnableVertexAttribArray(1);

	vbo.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
