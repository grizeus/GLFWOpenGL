#pragma once
#ifdef _WIN32
#include <glad/glad.h>
#elif __linux__
#include <GLES3/gl3.h>
#include <GL/gl.h>
#endif
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

inline void strip_draw(const std::vector<draw_strip_details>& details)
{
	for (const auto& d : details)
	{
		glBindVertexArray(d.vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, d.vert_count);
	}
	glBindVertexArray(0);
}

inline void draw_elems(const std::vector<draw_details>& details)
{
	for (const auto& d : details) 
	{
		glBindVertexArray(d.vao);
		//glDrawArrays(GL_LINES, 0, d.num_elements);
		glDrawElements(GL_TRIANGLES, d.num_elements, GL_UNSIGNED_INT, 0);
 		glBindVertexArray(0);
	}
	
}
