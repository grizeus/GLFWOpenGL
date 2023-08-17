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
	}
}

inline void draw_elems(const std::vector<draw_details>& details)
{
	for (const auto& d : details) 
	{
		glBindVertexArray(d.vao);
		// glDrawArrays(GL_LINES, 0, d.num_elements);
		glDrawElements(GL_TRIANGLES, d.num_elements, GL_UNSIGNED_INT, 0);
 		glBindVertexArray(0);
	}
	
}
