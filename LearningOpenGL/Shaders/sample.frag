#version 330 core

in vec3 currentPos;
in vec3 normal;
in vec3 color;
in vec2 uv;

uniform sampler2D albedo0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

out vec4 fragColor;

vec4 pointLight()
{
	vec3 lightVector = lightPos - currentPos;
	float dist = length(lightVector);
	float a = 0.03f;
	float b = 0.07f;
	float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);

	float ambient = 0.20f;

	vec3 Normal = normalize(normal);
	vec3 lightDir = normalize(lightVector);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDir = normalize(cameraPos - currentPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float specular = specularAmount * specularLight;

	return (texture(albedo0, uv) * (diffuse * intensity + ambient) + texture(specular0, uv).r * specular * intensity) * lightColor;
}

vec4 directionalLight()
{
	float ambient = 0.20f;

	vec3 Normal = normalize(normal);
	vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDir = normalize(cameraPos - currentPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float specular = specularAmount * specularLight;

	return (texture(albedo0, uv) * (diffuse + ambient) + texture(specular0, uv).r * specular) * lightColor;

}

vec4 spotLight()
{
	float outerCone = 0.60f;
	float innerCone = 0.95f;

	float ambient = 0.20f;

	vec3 Normal = normalize(normal);
	vec3 lightDir = normalize(lightPos - currentPos);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDir = normalize(cameraPos - currentPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float specular = specularAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
	float intensity = clamp((angle-outerCone)/ (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(albedo0, uv) * (diffuse * intensity + ambient) + texture(specular0, uv).r * specular * intensity) * lightColor;
}

void main() 
{ 
	fragColor = directionalLight(); 
}