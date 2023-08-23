#version 430 core
// Interpolated values from the vertex shaders
//in vec3 fragment_color;
in vec2 uv;

// Ouput data
out vec3 color;

uniform sampler2D texture_sampler;

void main(){
	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
//	color = fragment_color;
	color = texture(texture_sampler, uv).rgb;
}
