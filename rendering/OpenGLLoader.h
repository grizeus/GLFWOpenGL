#pragma once
#include <glad/glad.h>
#include <vector>
#include "../Vertex.h"

static draw_details upload_mesh(const std::vector<triangle_vertex>& verts, const std::vector<uint32_t> elem)
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

	return draw_details(vao, elem.size());
}

// TODO create overload for this type meshes (text_vertex)
//static draw_details upload_mesh(const std::vector<triangle_vertex>& verts, const std::vector<uint32_t> elem)
//{
//	if (verts.empty() || elem.empty())
//		throw("empty vector");
//
//	uint32_t vao, vbo, ebo;
//
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(triangle_vertex), &verts[0], GL_STATIC_DRAW); // or we can use verts.data()
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(triangle_vertex), (const void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(triangle_vertex), (const void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glGenBuffers(1, &ebo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elem.size() * sizeof(uint32_t), &elem[0], GL_STATIC_DRAW); // or we can use elem.data()
//
//	glBindVertexArray(0);
//	glDeleteBuffers(1, &vbo);
//	glDeleteBuffers(1, &ebo);
//
//	return draw_details(vao, elem.size());
//}


static void unload_mesh(std::vector<draw_details>& details)
{
	for (auto& d : details)
	{
		glDeleteBuffers(1, &d.vao);
	}
	details.clear();
}
