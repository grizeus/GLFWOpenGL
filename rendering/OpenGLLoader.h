#pragma once
#include <glad/glad.h>
#include <vector>
#include "../Vertex.h"

draw_details upload_mesh(std::vector<GLfloat> verts, std::vector<GLfloat> colors)
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

	return draw_details(vao_handle, static_cast<GLuint>(verts.size()));
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