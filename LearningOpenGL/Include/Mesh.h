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
	void Draw(Shader& shader, Camera& camera);

public:
	std::vector<Vertex>  vertices;
	std::vector<GLuint>  indices;
	std::vector<Texture> textures;

	VAO vao;
};

