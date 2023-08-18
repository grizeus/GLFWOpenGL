#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "Utilities.h"

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

inline void load_obj(const char* path, std::vector<GLfloat>& vertices)
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
		vertices.push_back(raw_v[i - 1].return_x());
		vertices.push_back(raw_v[i - 1].return_y());
		vertices.push_back(raw_v[i - 1].return_z());
	}
}

inline void load_vert_and_ind(const char* path, std::vector<GLfloat>& verts, std::vector<GLuint>& indices)
{
	std::vector<vec3> positions;
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
			positions.push_back(vec3(x, y, z));
		}
		else if (line.substr(0, 2) == "f ")
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
		//indices.push_back(std::stoi(i2));
		//indices.push_back(std::stoi(i3));
	}
	for (auto& i : indices)
	{
		verts.push_back(positions[i - 1].return_x());
		verts.push_back(positions[i - 1].return_y());
		verts.push_back(positions[i - 1].return_z());
	}
}
