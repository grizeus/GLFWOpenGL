#include "Camera.h"

camera::camera(GLuint shader, const int width, const int height)
    : m_cam_pos(0.0f, 0.0f, 3.0f)
    , m_cam_front(0.0f, 0.0f, -1.0f)
    , m_cam_up(0.0f, 1.0f, 0.0f)
    , m_delta_time(0)
    , m_win_width(width)
    , m_win_height(height)
    , m_model(1.0f)
{
    m_matrix_id = glGetUniformLocation(shader, "MVP");

    // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
    float aspect_ratio = static_cast<float>(m_win_width) / static_cast<float>(m_win_height);
    m_fov = glm::radians(45.0f);
    constexpr float NEAR = 0.1f;
    constexpr float FAR = 1000.0f;
    m_projection = glm::perspective(m_fov, aspect_ratio, NEAR, FAR);

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        m_cam_pos,
        m_cam_pos + m_cam_front,
        m_cam_up  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Our m_modelViewProjection : multiplication of our 3 matrices
    m_mvp = m_projection * View * m_model; // Remember, matrix multiplication is the other way around
}

camera::~camera()
{ }

void camera::on_render()
{
    glm::mat4 view = glm::lookAt(
        m_cam_pos,
        m_cam_pos + m_cam_front,
        m_cam_up  // Head is up (set to 0,-1,0 to look upside-down)
    );
    m_mvp = m_projection * view * m_model;
    glUniformMatrix4fv(m_matrix_id, 1, GL_FALSE, &m_mvp[0][0]);
}

void camera::on_event(const event& e)
{
    if (e.get_type() == etype::key_pressed)
    {
        const key_pressed_event& inside_event = dynamic_cast<const key_pressed_event&>(e);
        float cam_speed = static_cast<float>(2.5 * m_delta_time);
        if (inside_event.get_key_code() == key_code::W)
            m_cam_pos += cam_speed * m_cam_front;
        if (inside_event.get_key_code() == key_code::S)
            m_cam_pos -= cam_speed * m_cam_front;
        if (inside_event.get_key_code() == key_code::A)
            m_cam_pos -= glm::normalize(glm::cross(m_cam_front, m_cam_up)) * cam_speed;
        if (inside_event.get_key_code() == key_code::D)
            m_cam_pos += glm::normalize(glm::cross(m_cam_front, m_cam_up)) * cam_speed;
    }
}
