#version 330 core

uniform float time;
uniform vec2 screenRes;
uniform vec2 mousePos;

out vec4 FragColor;

float plot(vec2 st) { 

	return smoothstep(0.02, 0.0, abs(st.y - st.x)); 
}

void main() {
	
	vec2 normpix = gl_FragCoord.xy / screenRes.xy;
    vec3 color = vec3((smoothstep(0.0, 0.2, abs(sin(normpix.x + sin(abs(time)))))));

	FragColor = vec4(color, 1.0);

}