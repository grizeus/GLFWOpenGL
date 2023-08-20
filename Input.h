#pragma once
#include "events/EventSubscriber.h"
#include "rendering/Renderer.h"

#include <iostream>

class input : public event_subscriber
{
public:
    input(window_ptr window) : m_window(window) { }
    ~input() = default;

    inline void on_event(const event& e) override;
private:
    window_ptr m_window;
};

void input::on_event(const event& e)
{
    if (e.get_type() == etype::key_pressed)
    {
        const key_pressed_event* inside_event = dynamic_cast<const key_pressed_event*>(&e);
        if (inside_event->get_key_code() == key_code::ESCAPE) // TODO correctly cast GLFW scancode into enums and vice versa
            glfwSetWindowShouldClose(m_window.get(), true);
    }
}
//void process_input(GLFWwindow* window, float delta_time, camera cam)
//{
    /*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float camera_speed = static_cast<float>(2.5 * delta_time);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cam.m_cam_pos += camera_speed * cam.m_cam_front;
        std::cout << "cam pos " << cam.m_cam_pos.x << ":" << cam.m_cam_pos.y << ":" << cam.m_cam_pos.z << "\n";
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cam.m_cam_pos -= camera_speed * cam.m_cam_front;
        std::cout << "cam pos " << cam.m_cam_pos.x << ":" << cam.m_cam_pos.y << ":" << cam.m_cam_pos.z << "\n";
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cam.m_cam_pos -= glm::normalize(glm::cross(cam.m_cam_front, cam.m_cam_up)) * camera_speed;
        std::cout << "cam pos " << cam.m_cam_pos.x << ":" << cam.m_cam_pos.y << ":" << cam.m_cam_pos.z << "\n";
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cam.m_cam_pos += glm::normalize(glm::cross(cam.m_cam_front, cam.m_cam_up)) * camera_speed;
        std::cout << "cam pos " << cam.m_cam_pos.x << ":" << cam.m_cam_pos.y << ":" << cam.m_cam_pos.z << "\n";
    }*/
//}