#version 330 core

in vec3 color;
in vec2 uv;
in vec3 normal;
in vec3 currentPos;

out vec4 fragColor;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main() 
{ 
	float ambient = 0.20f;

	vec3 Normal = normalize(normal);
	vec3 lightDir = normalize(lightPos - currentPos);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDir = normalize(cameraPos - currentPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float specular = specularAmount * specularLight;


	fragColor = texture(tex0, uv) * lightColor * (diffuse + ambient + specular); 
}