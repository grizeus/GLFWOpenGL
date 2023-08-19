#pragma once

#include "rendering/Camera.h"
#include <iostream>

void process_input(GLFWwindow* window, float delta_time, camera cam)
{
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
}