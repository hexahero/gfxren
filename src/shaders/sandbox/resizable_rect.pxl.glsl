#version 330 core

uniform float time;
uniform vec2 screenRes;
uniform vec2 mousePos;

out vec4 FragColor;

void main() {
	
	vec2 pixCoordNormalized = gl_FragCoord.xy / screenRes.xy;
    vec2 mouseCoordNormalized = mousePos.xy / screenRes.xy;

    vec2 btmL = step(vec2(mouseCoordNormalized), pixCoordNormalized.xy);
    vec2 tpR = step(vec2(mouseCoordNormalized), 1.0 - pixCoordNormalized.xy);

    float color = btmL.x * btmL.y * tpR.x * tpR.y;

	FragColor = vec4(color, 0.0, 0.5, 1.0);

}
