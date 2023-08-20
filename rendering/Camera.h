#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../events/EventSubscriber.h"

class camera : public event_subscriber
{
public:
	camera(GLuint shader, const int width, const int height);
	~camera();
	void on_render();

	void on_event(const event& e) override;

	inline float get_fov() const { return m_fov; }
	
private:
	glm::vec3 m_cam_pos;
	glm::vec3 m_cam_front;
	glm::vec3 m_cam_up;
	GLuint m_matrix_id;
	glm::mat4 m_mvp;
	float m_fov;
};

