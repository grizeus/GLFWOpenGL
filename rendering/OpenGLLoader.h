#pragma once
#include <glad/glad.h>
#include <vector>
#include "../Vertex.h"

draw_details upload_mesh(const std::vector<triangle_vertex>& verts, const std::vector<uint32_t> elem)
{
	if (verts.empty() || elem.empty())
		throw("empty vector");

	uint32_t vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(triangle_vertex), &verts[0], GL_STATIC_DRAW); // or we can use verts.data()
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(triangle_vertex), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(triangle_vertex), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elem.size() * sizeof(uint32_t), &elem[0], GL_STATIC_DRAW); // or we can use elem.data()

	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	return draw_details(vao, static_cast<uint32_t>(elem.size()));
}

draw_details upload_mesh(const GLfloat* verts, const GLfloat* colors, const int v_count,
  const GLuint* elems, const int e_count)
{
	GLuint vbo_handles[2];
	glGenBuffers(2, vbo_handles);
	GLuint position_buffer_handle = vbo_handles[0];
	GLuint color_buffer_handle    = vbo_handles[1];

	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_handle);
	glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat), verts, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, color_buffer_handle);
	glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat), colors, GL_STATIC_DRAW);

	GLuint vao_handle;
	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);

	glEnableVertexAttribArray(0); // pos
	glEnableVertexAttribArray(1); // col

	glBindVertexBuffer(0, position_buffer_handle, 0, sizeof(GLfloat) * 3);
	glBindVertexBuffer(1, color_buffer_handle, 0, sizeof(GLfloat) * 3);

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);

	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);

	GLuint elem_handle;
	glGenBuffers(1, &elem_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem_handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, e_count * sizeof(GLuint), elems, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glDeleteBuffers(2, vbo_handles);
	glDeleteBuffers(1, &elem_handle);

	return draw_details(vao_handle, static_cast<uint32_t>(e_count));
}

draw_details upload_cube(std::vector<GLfloat> verts, std::vector<GLfloat> colors)
{
	GLuint vao_handle;
	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), &verts[0], GL_STATIC_DRAW);
	

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // pos
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
	glEnableVertexAttribArray(1); // col
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glBindVertexArray(0);

	return draw_details(vao_handle, verts.size());
}

draw_strip_details upload_mesh(const GLfloat* verts, const GLuint v_count)
{
	GLuint vao_handle;
	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);


	GLuint vbo_handle;
	glGenBuffers(1, &vbo_handle);
	GLuint position_buffer_handle = vbo_handle;
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer_handle);
	glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat), verts, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glBindVertexBuffer(0, position_buffer_handle, 0, sizeof(GLfloat) * 2);
	glVertexAttribFormat(0, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);  // map to shader

	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo_handle);

	std::cout << "draw strip:\n" << " -vao: " << vao_handle << "\n -count: " << v_count << '\n';

	return draw_strip_details(vao_handle, v_count);
}



template <typename T>
void unload_mesh(std::vector<T>& details)
{
	for (auto& d : details)
	{
		glDeleteBuffers(1, &d.vao);
	}
	details.clear();
}