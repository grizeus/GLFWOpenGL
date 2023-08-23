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
	//void set_shader_transforms(in)

	void on_event(const event& e) override;

	inline float get_fov() const { return m_fov; }
	inline glm::vec3 get_cam_pos() const { return m_cam_pos; }
	inline glm::vec3 get_cam_front() const { return m_cam_front; }
	inline glm::vec3 get_cam_up() const { return m_cam_up; }

	inline void set_cam_pos(glm::vec3 cam_pos) { m_cam_pos = cam_pos; }
	inline void set_cam_front(glm::vec3 cam_front) { m_cam_front = cam_front; }
	inline void set_cam_up(glm::vec3 cam_up) { m_cam_up = cam_up; }
	inline void set_delta_time(const double delta) { m_delta_time = delta; }

private:
	glm::vec3 m_cam_pos;
	glm::vec3 m_cam_front;
	glm::vec3 m_cam_up;
	GLuint m_matrix_id;
	glm::mat4 m_projection;
	glm::mat4 m_model;
	glm::mat4 m_mvp;
	float m_fov;
	float m_aspect_ratio;
	float m_last_ratio;
	float m_last_fov;
	double m_delta_time;
	unsigned int m_win_width;
	unsigned int m_win_height;
	static constexpr float m_NEAR = 0.1f;
	static constexpr float m_FAR = 100.0f;
};
