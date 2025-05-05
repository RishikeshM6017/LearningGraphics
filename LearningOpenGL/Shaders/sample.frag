#version 330 core

in vec3 color;
in vec2 uv;

out vec4 fragColor;

uniform sampler2D tex0;

void main() 
{ 
	fragColor = texture(tex0, uv); 
}