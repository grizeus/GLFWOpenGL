#pragma once
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Utilities.h"
#include <iostream>

inline void glfw_error_callback(int error, const char* description)
{
}

inline void glfw_window_close_callback(GLFWwindow* window)
{
}

inline void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

inline void glfw_mouse_movement_callback(GLFWwindow* window, double x, double y)
{
    //std::cout << "x: " << x << " y: " << y << '\n';
}

inline void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}
