#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol;
layout(location = 2) in vec2 aTex;

uniform mat4 camera;

out vec3 color;
out vec2 uv;

void main() 
{ 
	gl_Position = camera * vec4(aPos, 1.0);
	color = aCol;
	uv = aTex;
}