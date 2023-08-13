#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera
{
public:

	camera(GLuint shader, const int width, const int height);
	~camera();
	void uniform_matrix();
private:
	GLuint m_matrix_id;
	glm::mat4 m_mvp;
};

