#version 330 core

out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture_default;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

uniform bool isTextured = true;

void main() {

    if (isTextured) 
        FragColor = texture(texture_default, TexCoord);
    else 
        FragColor = vec4(0.5f, 0.5f, 0.5, 1.0f);
    
}