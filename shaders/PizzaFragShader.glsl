#version 430
out vec4 fragColor;
// uniform vec2 uResolution;

void main() {
	vec3 color = vec3(0);
	
	if (gl_FragCoord.x > 700) {
		color.x = .7;
	}

	if (gl_FragCoord.y > 500) {
		color.y = .7;
	}

	fragColor = vec4(color, 1.0);
}