#pragma once

#include <glad/glad.h>
#include <vector>

struct draw_details
{
	draw_details(GLuint v, GLuint e)
		: vao(v), num_elements(e)
	{}
	GLuint vao = 0;
	GLuint num_elements = 0;
};

using vec_glfloat = std::vector<GLfloat>;

class object
{
public:
	object(const char* path);
	~object();
	
	void upload_mesh(const GLuint& handle);
	void draw();
	void set_vertices(vec_glfloat& verts);
	void set_colors(vec_glfloat& colors);
private:
	vec_glfloat m_vertices;
	vec_glfloat m_colors;
	std::vector<draw_details> m_draw_details;
};
