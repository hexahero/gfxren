#version 330 core

#define SOLID_COLOR 		1
#define SURFACE_NORMALS 	2
#define TEXTURE_ONLY 		3
#define ILLUMINATED 		4

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

in vec3 fragmentPosition;

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

uniform float lightLinear = 0.045f;
uniform float lightQuadratic = 0.0075f;

uniform float ambientIntensity = 1.0f;
uniform float specularIntensity = 0.0f;

uniform vec4 solidColor = vec4(0.15f, 0.15f, 0.15f, 1.0f);

vec3 lightVector 		= lightPos - FragPos;
vec3 normalNormalized 	= normalize(Normal);
vec3 lightDirection 	= normalize(lightVector);
vec3 viewDirection 		= normalize(cameraPos - FragPos);

float calculate_attenuation(float lightLinear, float lightQuadratic, vec3 lightVector) {
	
	float lightDistance = length(lightVector);
	
	return 1.0f / (1.0f + (lightLinear * lightDistance) + (lightQuadratic * pow(lightDistance, 2)));
}
	
float calculate_diffusion() {

	return max(dot(normalNormalized, lightDirection), 0.0f);
}

float calculate_specularity() {

	vec3 reflectionDirection = reflect(-lightDirection, normalNormalized);
	
	return pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8) * specularIntensity;
}

void main() {
	
	float attenuation = calculate_attenuation(lightLinear, lightQuadratic, lightVector);
	float diffusion = attenuation * calculate_diffusion();
	float specularity = attenuation * calculate_specularity();
	
	switch(pixelMode) {
	
		case SOLID_COLOR:
			FragColor = solidColor * attenuation * lightColor * (ambientIntensity + diffusion + specularity);
			FragColor.a = 1.0f;
			break;
			
		case SURFACE_NORMALS:
			FragColor = vec4(normalNormalized.x, normalNormalized.y, normalNormalized.z, 1.0f) * ambientIntensity;
			FragColor.a = 1.0f;
			break;
			
		case TEXTURE_ONLY:
			FragColor = texture(texture_default, TexCoords);
			break;
			
		case ILLUMINATED:
			FragColor = texture(texture_default, TexCoords) * attenuation * lightColor * (ambientIntensity + diffusion + specularity);
			FragColor.a = 1.0f;
			break;
		
	}
	
}