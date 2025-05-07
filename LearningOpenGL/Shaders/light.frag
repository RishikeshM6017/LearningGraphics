#version 330 core

in vec3 color;

uniform vec4 lightColor;

out vec4 fragColor;

void main() 
{ 
	fragColor = lightColor; 
}