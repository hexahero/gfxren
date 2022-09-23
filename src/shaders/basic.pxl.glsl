#version 330 core

#define SOLID_COLOR 		1
#define SURFACE_NORMALS 	2
#define TEXTURE_ONLY 		3
#define ILLUMINATED 		4

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform float time;
uniform vec2 screenRes;
uniform vec3 cameraPos;
uniform vec2 mousePos;

uniform int pixelMode = TEXTURE_ONLY;

uniform sampler2D texture_default;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

uniform vec3 lightPos;
uniform vec4 lightColor;
uniform float ambientIntensity = 1.0f;
uniform float specularIntensity = 0.0f;

void main() {

	// Calculate diffusion
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - FragPos);

	float diffusion = max(dot(normal, lightDirection), 0.0f);

	// Calculate specularity
	vec3 viewDirection = normalize(cameraPos - FragPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	
	float specularity = specularAmount * specularIntensity;
	
	switch(pixelMode) {
	
		case SOLID_COLOR:
			FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
			break;
			
		case SURFACE_NORMALS:
			FragColor = vec4(normal.x, normal.y, normal.z, 1.0f) * ambientIntensity;
			FragColor.a = 1.0f;
			break;
			
		case TEXTURE_ONLY:
			FragColor = texture(texture_default, TexCoords);
			break;
			
		case ILLUMINATED:
			FragColor = texture(texture_default, TexCoords) * lightColor * (ambientIntensity + diffusion + specularity);
			FragColor.a = 1.0f;
			break;
		
	}
	
}