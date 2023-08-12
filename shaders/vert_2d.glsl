#version 430
layout (location = 1) in vec3 vertexColor;
out vec3 fragColor;
void main()
{
	fragColor = vertexColor;
}