#pragma once
#include <glad/glad.h>
#include <vector>
#include "../Vertex.h"

void draw(const std::vector<draw_details>& details)
{
	for (const auto& d : details)
	{
		glBindVertexArray(d.vao);
		glDrawElements(GL_TRIANGLES, d.num_elements, GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}

//static void text_draw(const std::vector<draw_details>& details)
//{
//	for (const auto& d : details)
//	{
//		glBindVertexArray(d.vao);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//	}
//	glBindVertexArray(0);
//}
