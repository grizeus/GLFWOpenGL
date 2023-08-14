#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "Utilities.h"

void load_obj(const char* path, std::vector<GLfloat>& vertices)
{
	std::vector<GLfloat> raw_v;
	std::vector<GLfloat> raw_vn;
	std::vector<GLfloat> raw_vt;
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
			raw_v.push_back(x);
			raw_v.push_back(y);
			raw_v.push_back(z);
		}
		else if (line.substr(0, 2) == "vn")
		{
			std::istringstream iss(line);
			std::string c;
			GLfloat x, y, z;
			iss >> c >> x >> y >> z;
			raw_vn.push_back(x);
			raw_vn.push_back(y);
			raw_vn.push_back(z);
		}
		else if (line.substr(0, 2) == "vt")
		{
			std::istringstream iss(line);
			std::string c;
			GLfloat x, y;
			iss >> c >> x >> y;
			raw_vt.push_back(x);
			raw_vt.push_back(y);
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
	for (auto p : parts)
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
	for (auto& i : indices)
	{
		if (i % 3 == 2)
		{
			vertices.push_back(raw_v[indices[i]]);
		}
		else if (i % 3 == 1)
		{
			vertices.push_back(raw_vn[indices[i]]);
		}
		else if (i % 3 == 0)
		{
			vertices.push_back(raw_vt[indices[i]]);
		}
	}
}

void load_vert_and_ind(const char* path, std::vector<GLfloat>& raw_v, std::vector<GLuint>& indices)
{
	//std::vector<GLfloat> raw_v;
	/*std::vector<GLfloat> raw_vn;
	std::vector<GLfloat> raw_vt;*/
	//std::vector<GLuint> indices;
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
			raw_v.push_back(x);
			raw_v.push_back(y);
			raw_v.push_back(z);
		}
		/*else if (line.substr(0, 2) == "vn")
		{
			std::istringstream iss(line);
			std::string c;
			GLfloat x, y, z;
			iss >> c >> x >> y >> z;
			raw_vn.push_back(x);
			raw_vn.push_back(y);
			raw_vn.push_back(z);
		}
		else if (line.substr(0, 2) == "vt")
		{
			std::istringstream iss(line);
			std::string c;
			GLfloat x, y;
			iss >> c >> x >> y;
			raw_vt.push_back(x);
			raw_vt.push_back(y);
		}*/
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
	for (auto p : parts)
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
	/*for (auto& i : indices)
	{
		if (i % 3 == 2)
		{
			vertices.push_back(raw_v[indices[i]]);
		}
		else if (i % 3 == 1)
		{
			vertices.push_back(raw_vn[indices[i]]);
		}
		else if (i % 3 == 0)
		{
			vertices.push_back(raw_vt[indices[i]]);
		}
	}*/
}
