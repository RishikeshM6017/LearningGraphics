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


void Mesh::Draw(Shader& shader, Camera& camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
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

	glm::mat4 translationMatrix	= glm::mat4(1.0f);
	glm::mat4 rotationMatrix	= glm::mat4(1.0f);
	glm::mat4 scaleMatrix		= glm::mat4(1.0f);
	
	translationMatrix	= glm::translate(translationMatrix, translation);
	rotationMatrix		= glm::mat4_cast(rotation);
	scaleMatrix			= glm::scale(scaleMatrix, scale);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"	), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"		), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"		), 1, GL_FALSE, glm::value_ptr(matrix));

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
