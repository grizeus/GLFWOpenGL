#pragma once

struct draw_details
{
	draw_details(GLuint v, GLuint e)
		: vao(v), num_elements(e)
	{}
	GLuint vao = 0;
	GLuint num_elements = 0;
};

struct draw_strip_details
{
	draw_strip_details(GLuint v, GLuint vc)
		: vao(v), vert_count(vc)
	{ }
	GLuint vao = 0;
	GLuint vert_count = 0;
};