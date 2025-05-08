#pragma once

#include <vector>
#include <GLM/glm.hpp>
#include <GLAD/glad.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 uv;

};

class VBO
{
public:
	VBO(std::vector<Vertex> &vertices);

public:
	void Bind();
	void Unbind();
	void Delete();

public:
	unsigned int ID;
};

