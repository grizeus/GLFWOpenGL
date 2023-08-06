#pragma once
#include <glad/glad.h>
#include <vector>
#include "../Vertex.h"

static void draw(const std::vector<draw_details>& details)
{
	for (const auto& d : details)
	{
		glBindVertexArray(d.vao);
		glDrawElements(GL_TRIANGLES, d.numElements, GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}
