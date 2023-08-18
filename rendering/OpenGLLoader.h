#pragma once
#include <glad/glad.h>
#include <vector>
#include "../DrawDetails.h"

inline draw_details upload_mesh(const std::vector<GLfloat>& verts, const std::vector<GLfloat>& colors)
{
	if (verts.empty() || colors.empty())
		throw ("Draw details is empty");
	GLuint vao, vertex_buf, color_buf;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertex_buf);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &color_buf);
	glBindBuffer(GL_ARRAY_BUFFER, color_buf);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // verts
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1); // colors
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);

	return draw_details(vao, static_cast<GLuint>(verts.size()));
}

/* TODO transform this in class destructor*/
template <typename T>
void unload_mesh(std::vector<T>& details)
{
	for (auto& d : details)
	{
		glDeleteBuffers(1, &d.vao);
	}
	details.clear();
}
