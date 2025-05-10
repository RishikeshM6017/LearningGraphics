#pragma once

#include <JSON/json.hpp>

#include "Mesh.h"

using JSON = nlohmann::json;

class Model
{
public:
	Model(const char* file);

public:
	std::vector<unsigned char>  GetData();
	std::vector<GLfloat>		GetFloats(JSON accessor);
	std::vector<GLuint>			GetIndices(JSON accessor);

	std::vector<glm::vec2> GroupFloatsVec2(std::vector<GLfloat> floatVec);
	std::vector<glm::vec3> GroupFloatsVec3(std::vector<GLfloat> floatVec);
	std::vector<glm::vec4> GroupFloatsVec4(std::vector<GLfloat> floatVec);

	std::vector<Vertex>  AssembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> uv);
	
	std::vector<Texture> GetTextures();
	
	void LoadMesh(unsigned int meshIndex);

	void TraverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	void Draw(Shader& shader, Camera& camera);

private:
	const char* file;
	std::vector<unsigned char> data;
	
	std::vector<std::string>	loadedTextureNames;
	std::vector<Texture>		loadedTextures;

	std::vector<Mesh>			meshes;
	std::vector<glm::vec3>		translations;
	std::vector<glm::quat>		rotations;
	std::vector<glm::vec3>		scales;
	std::vector<glm::mat4>		matrices;
	JSON json;

};

