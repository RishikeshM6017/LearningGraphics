#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec3 aCol;
layout(location = 3) in vec2 aTex;

uniform mat4 camera;
uniform mat4 model;

out vec3 currentPos;
out vec3 normal;
out vec3 color;
out vec2 uv;



void main() 
{ 
	currentPos = vec3(model * vec4(aPos, 1.0f));
	normal  = aNor;
	color	= aCol;
	uv		= aTex;
	
	gl_Position = camera * vec4(currentPos, 1.0f);
}