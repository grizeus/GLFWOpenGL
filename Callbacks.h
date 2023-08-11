#pragma once
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Utilities.h"
#include "shaders/Shader.h"
#include <iostream>

extern GLSL_shader* cursor_shader;
extern GLSL_shader* overlay_shader;


void glfw_error_callback(int error, const char* description)
{
    write_log(description);
    throw("glfw error");
}

void glfw_window_close_callback(GLFWwindow* window)
{
    write_log("Window closed\n");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::string size = "Window resized to " + std::to_string(width) + "x" + std::to_string(height) + " \n";
    write_log(size.c_str());
    glViewport(0, 0, width, height);
    overlay_shader->use();
    overlay_shader->set_vec2("uResolution", glm::vec2(width, height));
}

void glfw_mouse_movement_callback(GLFWwindow* window, double x, double y)
{
    cursor_shader->use();
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    cursor_shader->set_vec2("uMousePos", glm::vec2(x, height - y));
    std::cout << "x: " << x << " y: " << y << '\n';
}
