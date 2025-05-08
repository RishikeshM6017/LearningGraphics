#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices  = indices;
	Mesh::textures = textures;

	vao = VAO();
	vao.Bind();

	VBO vbo = VBO(vertices);
	EBO ebo = EBO(indices);

	vao.LinkAttribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) 0);
	vao.LinkAttribute(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(GLfloat)));
	vao.LinkAttribute(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(GLfloat)));
	vao.LinkAttribute(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(GLfloat)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	shader.Activate();

	vao.Bind();

	GLuint diffuseCount  = 0;
	GLuint specularCount = 0;

	for (GLuint i = 0; i < textures.size(); i++)
	{
		std::string count;
		std::string type = textures[i].type;

		if (type == "albedo")
		{
			count = std::to_string(diffuseCount++);
		}
		else if (type == "specular")
		{
			count = std::to_string(specularCount++);
		}

		textures[i].Link(shader, (type + count).c_str(), i);
		textures[i].Bind();
	}

	glUniform3f(glGetUniformLocation(shader.ID, "cameraPos"), camera.position.x, camera.position.y, camera.position.z);
	camera.Link(shader, "camera");

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
