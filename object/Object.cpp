#include "Object.h"
#include "../utilities/Utilities.h"
#include "../utilities/Query.h"

namespace
{
	struct vec3
	{
		vec3(GLfloat x, GLfloat y, GLfloat z)
			:m_x(x), m_y(y), m_z(z)
		{}
		~vec3()
		{}
		inline GLfloat return_x() { return m_x; }
		inline GLfloat return_y() { return m_y; }
		inline GLfloat return_z() { return m_z; }
	private:
		GLfloat m_x, m_y, m_z;
	};
}

object::object(const char* path)
{
	std::vector<vec3> raw_v;
	std::vector<int> indices;
	std::vector<std::string> parts;
	std::stringstream ss(read_to_string(path));
	std::string line;
	while (std::getline(ss, line))
	{
		if (line.substr(0,2) == "v ")
		{
			std::istringstream iss(line);
			char c;
			GLfloat x, y, z;
			iss >> c >> x >> y >> z;
			raw_v.push_back(vec3(x, y, z));
		}
		else if (line[0] == 'f')
		{
			std::istringstream iss(line);
			std::string part1, part2, part3, part4;
			char c;
			iss >> c >> part1 >> part2 >> part3;
			parts.push_back(part1);
			parts.push_back(part2);
			parts.push_back(part3);
		}
	}
	// separate 1 index in triplet for vertex coord
	for (auto& p : parts)
	{
		std::istringstream iss(p);
		std::string i1, i2, i3;
		std::getline(iss, i1, '/');
		std::getline(iss, i2, '/');
		std::getline(iss, i3, '/');
		indices.push_back(std::stoi(i1));
	}
	for (auto& i : indices)
	{
		m_vertices.push_back(raw_v[i - 1].return_x());
		m_vertices.push_back(raw_v[i - 1].return_y());
		m_vertices.push_back(raw_v[i - 1].return_z());
	}
}

object::~object()
{
	for (auto& d : m_draw_details)
	{
		glDeleteBuffers(1, &d.vao);
	}
	m_draw_details.clear();
	m_colors.clear();
	m_vertices.clear();
}

void object::upload_mesh(const GLuint& handle)
{
	if (m_vertices.empty() || m_colors.empty())
		throw ("Draw details is empty");
	GLuint vao, vertex_buf, color_buf;
	const GLint vertex_count = 3;
	const GLsizei stride = 0;
	const void* offset = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertex_buf);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &color_buf);
	glBindBuffer(GL_ARRAY_BUFFER, color_buf);
	glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(GLfloat), m_colors.data(), GL_STATIC_DRAW);

	GLint vertex_position;
	get_vertex_location(handle, "vertex_position", vertex_position);
	glEnableVertexAttribArray(vertex_position); // verts
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
	glVertexAttribPointer(vertex_position, vertex_count, GL_FLOAT, GL_FALSE, stride, offset);

	GLint vertex_color;
	get_vertex_location(handle, "vertex_color", vertex_color);
	glEnableVertexAttribArray(vertex_color); // colors
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
	glVertexAttribPointer(vertex_color, vertex_count, GL_FLOAT, GL_FALSE, stride, offset);

	glBindVertexArray(0);
	glDeleteBuffers(1, &vertex_buf);
	glDeleteBuffers(1, &color_buf);

	m_draw_details.push_back(draw_details(vao, static_cast<GLuint>(m_vertices.size())));
}

void object::draw()
{
	for (const auto& d : m_draw_details)
	{
		glBindVertexArray(d.vao);
		glDrawArrays(GL_TRIANGLES, 0, d.num_elements);
		glBindVertexArray(0);
	}
}

void object::set_vertices(vec_glfloat& verts)
{
	if (!m_vertices.empty())
		m_vertices.clear();
	m_vertices = verts;
}

void object::set_colors(vec_glfloat& colors)
{
	if (!m_colors.empty())
		m_colors.clear();
	m_colors = colors; 
}
