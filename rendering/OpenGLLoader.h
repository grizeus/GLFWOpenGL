#pragma once
#include <glad/glad.h>
#include <vector>
#include "../DrawDetails.h"

inline draw_details upload_mesh_array(const std::vector<GLfloat>& verts, const std::vector<GLfloat>& colors)
{
	if (verts.empty() || colors.empty())
		throw ("Draw details is empty");
	GLuint vao, ;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return draw_details(vao, static_cast<GLuint>(verts.size()));
}

inline draw_details upload_mesh_elements(const std::vector<GLfloat>& verts, const std::vector<GLuint>& indices)
{
	GLuint vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and bind VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

	// Create and bind EBO
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// Set up vertex attribute pointer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// Unbind VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return draw_details(vao, static_cast<GLuint>(indices.size()));
}

inline draw_details upload_mesh_elems_cols(const std::vector<GLfloat>& verts, const std::vector<GLfloat>& colors, const std::vector<GLuint>& indices)
{
	if (verts.empty() || colors.empty() || indices.empty())
		throw ("Draw details is empty");
	GLuint vao, vbo[2], ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and bind VBO
	glGenBuffers(2, vbo);
	GLuint pos_vbo = vbo[0];
	GLuint col_vbo = vbo[1];

	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, col_vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // pos
	glEnableVertexAttribArray(1); // col

	glBindVertexBuffer(0, pos_vbo, 0, sizeof(GLfloat) * 3);
	glBindVertexBuffer(1, col_vbo, 0, sizeof(GLfloat) * 3);

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);

	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);

	// Create and bind EBO
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// Unbind VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	/*glDeleteBuffers(2, vbo);
	glDeleteBuffers(1, &ebo);*/


	return draw_details(vao, static_cast<GLuint>(indices.size()));
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
