#include "Object.h"
#include "../utilities/Utilities.h"
#include "../utilities/Query.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

	struct vec2
	{
		vec2(GLfloat x, GLfloat y)
			:m_x(x), m_y(y)
		{}
		~vec2()
		{}
		inline GLfloat return_x() { return m_x; }
		inline GLfloat return_y() { return m_y; }
	private:
		GLfloat m_x, m_y;
	};
}

object::object(const char* path)
	:m_texture(0)
{
	std::vector<vec3> raw_v;
	std::vector<vec3> raw_vn;
	std::vector<vec2> raw_vt;
	std::vector<int> indices;
	std::vector<std::string> parts;
	std::stringstream ss(read_to_string(path));
	std::string line;
	while (std::getline(ss, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream iss(line);
			char c;
			GLfloat x, y, z;
			iss >> c >> x >> y >> z;
			raw_v.push_back(vec3(x, y, z));
		}
		else if (line.substr(0, 2) == "vn")
		{
			std::istringstream iss(line);
			char c;
			GLfloat x, y, z;
			iss >> c >> x >> y >> z;
			raw_vn.push_back(vec3(x, y, z));
		}
		else if (line.substr(0, 2) == "vt")
		{
			std::istringstream iss(line);
			char c;
			GLfloat x, y;
			iss >> c >> x >> y;
			raw_vt.push_back(vec2(x, y));
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
	for (auto& p : parts)
	{
		std::istringstream iss(p);
		std::string i1, i2, i3;
		std::getline(iss, i1, '/');
		std::getline(iss, i2, '/');
		std::getline(iss, i3, '/');
		indices.push_back(std::stoi(i1));
		indices.push_back(std::stoi(i2));
		indices.push_back(std::stoi(i3));
	}
	// vertices
	for (int i = 0; i < indices.size(); i += 3)
	{
		m_vertices.push_back(raw_v[indices[i] - 1].return_x());
		m_vertices.push_back(raw_v[indices[i] - 1].return_y());
		m_vertices.push_back(raw_v[indices[i] - 1].return_z());
	}
	// uv
	for (int i = 1; i < indices.size(); i += 3)
	{
		m_uv.push_back(raw_vt[indices[i] - 1].return_x());
		m_uv.push_back(raw_vt[indices[i] - 1].return_y());
	}
	// normales
	for (int i = 2; i < indices.size(); i += 3)
	{
		m_normales.push_back(raw_vn[indices[i] - 1].return_x());
		m_normales.push_back(raw_vn[indices[i] - 1].return_y());
		m_normales.push_back(raw_vn[indices[i] - 1].return_z());
	}
}

void object::load_textured_obj(const char* path)
{
	if (!m_vertices.empty() || !m_uv.empty() || !m_normales.empty())
	{
		m_vertices.clear();
		m_uv.clear();
		m_normales.clear();
	}
	std::vector<vec3> raw_v;
	std::vector<vec3> raw_vn;
	std::vector<vec2> raw_vt;
	std::vector<int> indices;
	std::vector<std::string> parts;
	std::stringstream ss(read_to_string(path));
	std::string line;
	while (std::getline(ss, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream iss(line);
			char c;
			GLfloat x, y, z;
			iss >> c >> x >> y >> z;
			raw_v.push_back(vec3(x, y, z));
		}
		else if (line.substr(0, 2) == "vn")
		{
			std::istringstream iss(line);
			char c;
			GLfloat x, y, z;
			iss >> c >> x >> y >> z;
			raw_vn.push_back(vec3(x, y, z));
		}
		else if (line.substr(0, 2) == "vt")
		{
			std::istringstream iss(line);
			char c;
			GLfloat x, y;
			iss >> c >> x >> y;
			raw_vt.push_back(vec2(x, y));
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
		indices.push_back(std::stoi(i2));
		indices.push_back(std::stoi(i3));
	}
	for (int i = 0; i < indices.size(); i += 3)
	{
		m_vertices.push_back(raw_v[indices[i] - 1].return_x());
		m_vertices.push_back(raw_v[indices[i] - 1].return_y());
		m_vertices.push_back(raw_v[indices[i] - 1].return_z());
	}
	for (int i = 1; i < indices.size(); i += 3)
	{
		m_uv.push_back(raw_vt[indices[i] - 1].return_x());
		m_uv.push_back(raw_vt[indices[i] - 1].return_y());
	}
	for (int i = 2; i < indices.size(); i += 3)
	{
		m_normales.push_back(raw_vn[indices[i] - 1].return_x());
		m_normales.push_back(raw_vn[indices[i] - 1].return_y());
		m_normales.push_back(raw_vn[indices[i] - 1].return_z());
	}
}

void object::load_BMP(const char* imagepath) {

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int data_pos;
	unsigned int image_size;
	unsigned int width, height;
	// Actual RGB data
	unsigned char* data;

	// Open the file
	FILE* file;
	fopen_s(&file, imagepath, "rb");
	if (!file)
		throw std::runtime_error("File could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n");

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if (fread(header, 1, 54, file) != 54) 
	{
		fclose(file);
		throw std::runtime_error("Not a correct BMP file\n");
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M')
	{
		fclose(file);
		throw std::runtime_error("Not a correct BMP file\n");
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E]) != 0) { fclose(file); throw std::runtime_error("Not a correct BMP file\n"); }
	if (*(int*)&(header[0x1C]) != 24) { fclose(file); throw std::runtime_error("Not a correct BMP file\n"); }

	// Read the information about the image
	data_pos = *(int*)&(header[0x0A]);
	image_size = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (image_size == 0)    image_size = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (data_pos == 0)      data_pos = 54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char[image_size];

	// Read the actual data from the file into the buffer
	fread_s(data, image_size, 1, image_size, file);

	// Everything is in memory now, the file can be closed.
	fclose(file);

	// Create one OpenGL texture
	GLuint texture;
	glGenTextures(1, &texture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	delete[] data;

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	m_texture = texture;
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
	m_uv.clear();
	m_normales.clear();
	glDeleteTextures(1, &m_texture);
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
	query_resource_location(handle, "vertex_position", vertex_position);
	glEnableVertexAttribArray(vertex_position); // verts
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
	glVertexAttribPointer(vertex_position, vertex_count, GL_FLOAT, GL_FALSE, stride, offset);

	GLint vertex_color;
	query_resource_location(handle, "vertex_color", vertex_color);
	glEnableVertexAttribArray(vertex_color); // colors
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
	glVertexAttribPointer(vertex_color, vertex_count, GL_FLOAT, GL_FALSE, stride, offset);

	glBindVertexArray(0);
	glDeleteBuffers(1, &vertex_buf);
	glDeleteBuffers(1, &color_buf);

	m_draw_details.push_back(draw_details(vao, static_cast<GLuint>(m_vertices.size())));
}

void object::upload_textured_mesh(const GLuint& handle)
{
	if (m_vertices.empty() || m_uv.empty())
		throw ("Draw details is empty");
	GLuint vao, vertex_buf, uv_buf;
	const GLint vertex_count = 3;
	const GLint uv_count = 2;
	const GLsizei stride = 0;
	const void* offset = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertex_buf);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &uv_buf);
	glBindBuffer(GL_ARRAY_BUFFER, uv_buf);
	glBufferData(GL_ARRAY_BUFFER, m_uv.size() * sizeof(GLfloat), m_uv.data(), GL_STATIC_DRAW);

	// set-up texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	GLuint texture_ID = glGetUniformLocation(handle, "texture_sampler");
	glUniform1i(texture_ID, 0);

	GLint vertex_position;
	query_resource_location(handle, "vertex_position", vertex_position);
	glEnableVertexAttribArray(vertex_position); // verts
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
	glVertexAttribPointer(vertex_position, vertex_count, GL_FLOAT, GL_FALSE, stride, offset);

	GLint vertex_uv;
	query_resource_location(handle, "vertex_uv", vertex_uv);
	glEnableVertexAttribArray(vertex_uv); // colors
	glBindBuffer(GL_ARRAY_BUFFER, uv_buf);
	glVertexAttribPointer(vertex_uv, uv_count, GL_FLOAT, GL_FALSE, stride, offset);

	glBindVertexArray(0);
	glDisableVertexAttribArray(vertex_position);
	glDisableVertexAttribArray(vertex_uv);
	glDeleteBuffers(1, &vertex_buf);
	glDeleteBuffers(1, &uv_buf);

	m_draw_details.push_back(draw_details(vao, static_cast<GLuint>(m_vertices.size())));
}

void object::upload_texture(const GLuint width, const GLuint height, const GLubyte* tex_data, bool hasAlpha)
{

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//try: https://stackoverflow.com/questions/23150123/loading-png-with-stb-image-for-opengl-texture-gives-wrong-colors
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (hasAlpha)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
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
