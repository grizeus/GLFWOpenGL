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
	inline glm::vec3 get_cam_pos() const { return m_cam_pos; }
	inline glm::vec3 get_front_pos() const { return m_cam_front; }
	inline glm::vec3 get_up_pos() const { return m_cam_up; }

	inline void set_cam_pos(glm::vec3 cam_pos) { m_cam_pos = cam_pos; }
	inline void set_front_pos(glm::vec3 cam_front) { m_cam_front = cam_front; }
	inline void set_up_pos(glm::vec3 cam_up) { m_cam_up = cam_up; }
private:
	glm::vec3 m_cam_pos;
	glm::vec3 m_cam_front;
	glm::vec3 m_cam_up;
	GLuint m_matrix_id;
	glm::mat4 m_mvp;
	float m_fov;
};

