#pragma once

#include <string>
#include <vector>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h" 

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

public:
	void Draw(Shader& shader, Camera& camera, glm::mat4 matrix = glm::mat4(1.0f), glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

public:
	std::vector<Vertex>  vertices;
	std::vector<GLuint>  indices;
	std::vector<Texture> textures;

	VAO vao;
};

