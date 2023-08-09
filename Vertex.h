#pragma once

struct triangle_vertex
{
	triangle_vertex(float x, float y, float z, float r, float g, float b)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}

	float pos[3];	// x y z
	float color[3];	// r g b
};

struct draw_details
{
	draw_details(GLuint v, GLuint e)
		: vao(v), num_elements(e)
	{}
	GLuint vao = 0;
	GLuint num_elements = 0;
};
