#include "Model.h"

Model::Model(const char* file)
{
	std::string text = LoadFromFile(file);
	json = JSON::parse(text);

	Model::file = file;
	data = GetData();

	TraverseNode(0);
}


std::vector<unsigned char>  Model::GetData()
{
	std::string bytesText;
	std::string uri = json["buffers"][0]["uri"];

	std::string fileStr = std::string(file);
	std::string fileDir = fileStr.substr(0, fileStr.find_last_of('/') + 1);
	bytesText = LoadFromFile((fileDir + uri).c_str());

	std::vector<unsigned char> data(bytesText.begin(), bytesText.end());

	return data;
}


std::vector<float>	Model::GetFloats(JSON accessor)
{
	std::vector<GLfloat> floatVec;

	unsigned int bufferViewIndex	= accessor.value("bufferView", 1);
	unsigned int count				= accessor["count"];
	unsigned int accessorByteOffset = accessor.value("byteOffset", 0);
	std::string  type				= accessor["type"];

	JSON bufferView = json["bufferViews"][bufferViewIndex];
	unsigned int byteOffset = bufferView.value("byteOffset", 0);

	unsigned int attributeCount;
	if		(type == "SCALAR") attributeCount = 1;
	else if (type == "VEC2")   attributeCount = 2;
	else if (type == "VEC3")   attributeCount = 3;
	else if (type == "VEC4")   attributeCount = 4;
	else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

	unsigned int dataStart  = byteOffset + accessorByteOffset;
	unsigned int dataLength = count * 4 * attributeCount;

	for (unsigned int i = dataStart; i < dataStart + dataLength; i)
	{
		unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
		float value;
		std::memcpy(&value, bytes, sizeof(float));
		floatVec.push_back((GLfloat)value);
	}

	return floatVec;
}

std::vector<GLuint>	Model::GetIndices(JSON accessor)
{
	std::vector<GLuint> indices;

	unsigned int bufferViewIndex	= accessor.value("bufferView", 0);
	unsigned int count				= accessor["count"];
	unsigned int accessorByteOffset = accessor.value("byteOffset", 0);
	unsigned int componentType		= accessor["componentType"];

	JSON bufferView = json["bufferViews"][bufferViewIndex];
	unsigned int byteOffset = bufferView.value("byteOffset", 0);

	unsigned int dataStart = byteOffset + accessorByteOffset;

	if (componentType == 5125)
	{
		for (unsigned int i = dataStart; i < dataStart + count * 4; i)
		{
			unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
			unsigned int  value;
			std::memcpy(&value, bytes, sizeof(unsigned int));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType == 5123)
	{
		for (unsigned int i = dataStart; i < dataStart + count * 2; i)
		{
			unsigned char  bytes[] = { data[i++], data[i++] };
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(unsigned short));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType == 5122)
	{
		for (unsigned int i = dataStart; i < dataStart + count * 2; i)
		{
			unsigned char  bytes[] = { data[i++], data[i++] };
			short value;
			std::memcpy(&value, bytes, sizeof(short));
			indices.push_back((GLuint)value);
		}
	}

	return indices;
}


std::vector<glm::vec2>	Model::GroupFloatsVec2(std::vector<GLfloat> floatVec)
{
	std::vector<glm::vec2> vector2;

	for (int i = 0; i < floatVec.size(); i)
	{
		vector2.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
	}

	return vector2;
}

std::vector<glm::vec3>	Model::GroupFloatsVec3(std::vector<GLfloat> floatVec)
{
	std::vector<glm::vec3> vector3;

	for (int i = 0; i < floatVec.size(); i)
	{
		vector3.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
	}

	return vector3;
}

std::vector<glm::vec4>	Model::GroupFloatsVec4(std::vector<GLfloat> floatVec)
{
	std::vector<glm::vec4> vector4;

	for (int i = 0; i < floatVec.size(); i)
	{
		vector4.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
	}

	return vector4;
}


std::vector<Vertex> Model::AssembleVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> uv)
{
	std::vector<Vertex> vertices;

	for (int i = 0; i < positions.size(); i++)
	{
		vertices.push_back(Vertex{ positions[i], normals[i], glm::vec3(1.0f, 1.0f, 1.0f), uv[i] });
	}

	return vertices;
}


std::vector<Texture> Model::GetTextures()
{
	std::vector<Texture> textures;
	std::string fileStr = std::string(file);
	std::string fileDir = fileStr.substr(0, fileStr.find_last_of('/') + 1);

	for (unsigned int i = 0; i < json["images"].size(); i++)
	{
		std::string texturePath = json["images"][i]["uri"];

		bool skip = false;
		for (unsigned int j = 0; j < loadedTextureNames.size(); j++)
		{
			if (loadedTextureNames[i] == texturePath)
			{
				textures.push_back(loadedTextures[i]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			if (texturePath.find("albedo") != std::string::npos)
			{
				Texture albedo = Texture((fileDir + texturePath).c_str(), "albedo", loadedTextures.size());
				textures.push_back(albedo);
				loadedTextures.push_back(albedo);
			}
			else if (texturePath.find("specular") != std::string::npos)
			{
				Texture specular = Texture((fileDir + texturePath).c_str(), "specular", loadedTextures.size());
				textures.push_back(specular);
				loadedTextures.push_back(specular);
			}
			/*else if (texturePath.find("metallic") != std::string::npos)
			{
				Texture albedo = Texture((fileDir + texturePath).c_str(), "metallic", unit++);
				textures.push_back(albedo);
			}
			else if (texturePath.find("roughness") != std::string::npos)
			{
				Texture albedo = Texture((fileDir + texturePath).c_str(), "roughness", unit++);
				textures.push_back(albedo);
			}
			else if (texturePath.find("occlusion") != std::string::npos)
			{
				Texture albedo = Texture((fileDir + texturePath).c_str(), "occlusion", unit++);
				textures.push_back(albedo);
			}
			else if (texturePath.find("orm") != std::string::npos)
			{
				Texture albedo = Texture((fileDir + texturePath).c_str(), "orm", unit++);
				textures.push_back(albedo);
			}*/
		}
	}

	return textures;
}


void Model::LoadMesh(unsigned int meshIndex)
{
	unsigned int positionsIndex = json["meshes"][meshIndex]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normalsIndex	= json["meshes"][meshIndex]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int uvIndex		= json["meshes"][meshIndex]["primitives"][0]["attributes"]["TEXCOORD_0"];
	unsigned int indicesIndex	= json["meshes"][meshIndex]["primitives"][0]["indices"];

	std::vector<glm::vec3>  positions	= GroupFloatsVec3(GetFloats(json["accessors"][positionsIndex]));
	std::vector<glm::vec3>	normals		= GroupFloatsVec3(GetFloats(json["accessors"][normalsIndex]));
	std::vector<glm::vec2>  uv			= GroupFloatsVec2(GetFloats(json["accessors"][uvIndex]));

	std::vector<Vertex>  vertices	= AssembleVertices(positions, normals, uv);
	std::vector<GLuint>	 indices	= GetIndices(json["accessors"][indicesIndex]);
	std::vector<Texture> textures	= GetTextures();

	meshes.push_back(Mesh(vertices, indices, textures));
}


void Model::TraverseNode(unsigned int nextNode, glm::mat4 matrix)
{
	JSON node = json["nodes"][nextNode];

	glm::vec3 translationNode = glm::vec3(0.0f, 0.0f, 0.0f);
	if (node.find("translation") != node.end())
	{
		float translationValue[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++)
		{
			translationValue[i] = (node["translation"][i]);
		}
		translationNode = glm::make_vec3(translationValue);
	}

	glm::quat rotationNode = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end())
	{
		float rotationValue[4] =
		{
			node["rotation"][3],
			node["rotation"][0],
			node["rotation"][1],
			node["rotation"][2]
		};
		rotationNode = glm::make_quat(rotationValue);
	}

	glm::vec3 scaleNode = glm::vec3(0.0f, 0.0f, 0.0f);
	if (node.find("translation") != node.end())
	{
		float scaleValue[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++)
		{
			scaleValue[i] = (node["translation"][i]);
		}
		scaleNode = glm::make_vec3(scaleValue);
	}

	glm::mat4 matrixNode = glm::mat4(1.0f);
	if (node.find("matrix") != node.end())
	{
		float matrixValue[16];
		for (unsigned int i = 0; i < node["matrix"].size(); i++)
		{
			matrixValue[i] = (node["matrix"][i]);
		}
		matrixNode = glm::make_mat4(matrixValue);
	}

	glm::mat4 translation	= glm::mat4(1.0f);
	glm::mat4 rotation		= glm::mat4(1.0f);
	glm::mat4 scale			= glm::mat4(1.0f);

	translation = glm::translate(translationNode);
	rotation	= glm::mat4_cast(rotationNode);
	scale		= glm::scale(scaleNode);

	glm::mat4 nextMatrixNode = matrix * matrixNode;// *translation* rotation* scale;

	if (node.find("mesh") != node.end())
	{
		translations.push_back(translationNode);
		rotations.push_back(rotationNode);
		scales.push_back(scaleNode);
		matrices.push_back(nextMatrixNode);

		LoadMesh(node["mesh"]);
	}

	if (node.find("children") != node.end())
	{
		for (unsigned int i = 0; i < node["children"].size(); i++)
			TraverseNode(node["children"][i], nextMatrixNode);
	}

}


void Model::Draw(Shader& shader, Camera& camera)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Mesh::Draw(shader, camera, matrices[i]);
	}
}
