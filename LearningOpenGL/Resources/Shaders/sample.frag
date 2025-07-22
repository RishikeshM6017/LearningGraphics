#version 460 core

in vec3 vertexColor;

out vec4 fragmentColor;

void main() 
{
	fragmentColor = vec4(1.0f, 1.0f, 1.0f, 1.0f); //vec4(vertexColor, 1.0f);
}