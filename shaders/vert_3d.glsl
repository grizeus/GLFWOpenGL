#version 430
layout (location=0) in vec3 pos;
uniform mat4 uProjectionMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
void main()
{
	vec4 final_pos = uProjectionMatrix * uModelMatrix * uViewMatrix * vec4(pos, 1.0);
//	vec4 final_pos = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(pos, 1.0); // mb this order
	gl_Position = final_pos;
}