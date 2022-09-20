#version 330 core

out vec4 FragColor;

uniform float time;
uniform vec2 screenRes;
uniform vec2 mousePos;

uniform vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

void main() {
	
	FragColor = lightColor;

}