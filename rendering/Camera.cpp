#include "Camera.h"


camera::camera(GLuint shader, const int width, const int height)
    : m_cam_pos(4.0f, 3.0f, -3.0f)
    , m_cam_front(-4.0f, -3.0f, 3.0f)
    , m_cam_up(0.0f, 1.0f, 0.0f)
    , m_last_ratio(0.0f)
    , m_last_fov(0.0f)
    , m_delta_time(0)
    , m_win_width(width)
    , m_win_height(height)
    , m_model(1.0f)
{
    m_matrix_id = glGetUniformLocation(shader, "MVP");

    // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
    m_aspect_ratio = static_cast<float>(m_win_width) / static_cast<float>(m_win_height);
    m_fov = glm::radians(45.0f);
    m_projection = glm::perspective(m_fov, m_aspect_ratio, m_NEAR, m_FAR);

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
    if (m_last_ratio != m_aspect_ratio || m_last_fov != m_fov)
        m_projection = glm::perspective(m_fov, m_aspect_ratio, m_NEAR, m_FAR);
    glm::mat4 view = glm::lookAt(
        m_cam_pos,
        m_cam_pos + m_cam_front,
        m_cam_up
    );
    m_mvp = m_projection * view * m_model;
    glUniformMatrix4fv(m_matrix_id, 1, GL_FALSE, &m_mvp[0][0]);
    m_last_ratio = m_aspect_ratio;
    m_last_fov = m_fov;
}

void camera::on_event(const event& e)
{
    switch (e.get_type())
    {
        case etype::key_pressed:
        {
            const key_pressed_event& inside_event = dynamic_cast<const key_pressed_event&>(e);
            float cam_speed = static_cast<float>(2.5 * m_delta_time);
            switch (inside_event.get_key_code())
            {
            case key_code::W:
                m_cam_pos += cam_speed * m_cam_front;
                break;
            case key_code::S:
                m_cam_pos -= cam_speed * m_cam_front;
                break;
            case key_code::A:
                m_cam_pos -= glm::normalize(glm::cross(m_cam_front, m_cam_up)) * cam_speed;
                break;
            case key_code::D:
                m_cam_pos += glm::normalize(glm::cross(m_cam_front, m_cam_up)) * cam_speed;
                break;
            case key_code::D1:
                m_cam_up = { 0.0f, 1.0f, 0.0f };
                break;
            case key_code::D2:
                m_cam_up = { 0.0f, -1.0f, 0.0f };
                break;
            default:
                break;
            }
            break;
        }
        case etype::window_resize:
        {
            const window_resize_event& inside_event = dynamic_cast<const window_resize_event&>(e);
            m_win_width = inside_event.get_width();
            m_win_height = inside_event.get_height();
            m_aspect_ratio = static_cast<float>(m_win_width) / static_cast<float>(m_win_height);
            break;
        }
        default:
            break;
    }
}
