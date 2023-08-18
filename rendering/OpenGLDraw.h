#pragma once
#include <glad/glad.h>
#include <vector>
#include "../DrawDetails.h"

inline void draw(const std::vector<draw_details>& details)
{
	for (const auto& d : details) 
	{
		glBindVertexArray(d.vao);
		glDrawArrays(GL_TRIANGLES, 0, d.num_elements);
		glBindVertexArray(0);
	}
}
