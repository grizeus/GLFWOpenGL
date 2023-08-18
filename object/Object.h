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

class object
{
public:
	object(const char* path);
	~object();
	
	void upload_mesh();
	void draw();
	void set_vertices(std::vector<GLfloat>& verts);
	void set_colors(std::vector<GLfloat>& colors);
private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_colors;
	std::vector<draw_details> m_draw_details;
};
