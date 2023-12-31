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

void strip_draw(const std::vector<draw_strip_details>& details)
{
	for (const auto& d : details)
	{
		glBindVertexArray(d.vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, d.vert_count);
	}
	glBindVertexArray(0);
}
