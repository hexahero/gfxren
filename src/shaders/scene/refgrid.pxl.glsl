#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform float time;
uniform vec2 screenRes;
uniform vec3 cameraPos;
uniform vec2 mousePos;

uniform sampler2D texture_default;

void main() {
	
	FragColor = texture(texture_default, TexCoords);

}