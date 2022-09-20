#version 330 core

uniform float time;
uniform vec2 screenRes;
uniform vec2 mousePos;

out vec4 FragColor;

void circle(vec2 center, vec4 color, float radius) {

	if (length(gl_FragCoord.xy - center) < radius) {
	
		FragColor += color;
	}
	else {
		
		FragColor = vec4(sin(time), sin(time), 1.0, 1.0);
	}
	
}

void main() {
	
	vec2 mouseCoordNormalized = mousePos.xy / screenRes.xy;
	
	circle(
		vec2(mousePos.x, -(mousePos.y - screenRes.y)), 
		vec4(1.0, mouseCoordNormalized.x, mouseCoordNormalized.y, 1.0),
		50.0
	);
	
}