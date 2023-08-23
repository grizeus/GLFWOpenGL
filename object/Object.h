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
	object() = default;
	object(const char* path);
	void load_textured_obj(const char* path);
	~object();
	
	void load_BMP(const char* imagepath);
	void upload_mesh(const GLuint& handle);
	void upload_textured_mesh(const GLuint& handle);
	void upload_texture(const GLuint width, const GLuint height, const GLubyte* tex_data, bool hasAlpha);
	void draw();
	void set_vertices(vec_glfloat& verts);
	void set_colors(vec_glfloat& colors);
	inline void set_texture(GLuint texture) { m_texture = texture; }
private:
	vec_glfloat m_vertices;
	vec_glfloat m_colors;
	vec_glfloat m_uv;
	vec_glfloat m_normales;
	std::vector<draw_details> m_draw_details;
	GLuint m_texture;
};
