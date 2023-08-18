#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class camera
{
public:
	camera(GLuint shader, const int width, const int height, const glm::vec3& cam_pos, const glm::vec3& fron_pos, const glm::vec3& up_pos);
	~camera();
	void on_render();
	float get_fov() { return m_fov; }
private:
	GLuint m_matrix_id;
	glm::mat4 m_mvp;
	float m_fov;
};

