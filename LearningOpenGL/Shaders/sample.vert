#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec3 aCol;
layout(location = 3) in vec2 aTex;

uniform mat4 camera;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


out vec3 currentPos;
out vec3 normal;
out vec3 color;
out vec2 uv;



void main() 
{ 
	currentPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0));
	normal  = aNor;
	color	= aCol;
	uv		= mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	
	gl_Position = camera * vec4(currentPos, 1.0);
}