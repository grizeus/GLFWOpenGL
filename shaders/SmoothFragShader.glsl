#version 430
out vec4 fragColor;

uniform vec2 uResolution;

float plot(vec2 st, float pct) {
	return smoothstep(pct - 0.02, pct, st.y) - smoothstep(pct, pct+0.02, st.y);
}

void main() {
	vec2 st= gl_FragCoord.xy/uResolution;
	float y = smoothstep(0.1, 0.9, st.x);
	vec3 color = vec3(y);
	float pct = plot(st,y);
	color = (1.0-pct) * color + pct * vec3(0.0, 1.0, 0.0);
	fragColor = vec4(color, 1.0);
}