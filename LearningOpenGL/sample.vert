#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;

uniform float scale;

out vec3 color;

void main() 
{ 
	gl_Position = vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
	color = aCol;
}