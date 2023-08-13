#pragma once
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Utilities.h"
#include <iostream>

void glfw_error_callback(int error, const char* description)
{
    write_log(description);
}

void glfw_window_close_callback(GLFWwindow* window)
{
    write_log("Window closed\n");
}

void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::string size = "Window resized to " + std::to_string(width) + "x" + std::to_string(height) + " \n";
    write_log(size.c_str());
    glViewport(0, 0, width, height);
}

void glfw_mouse_movement_callback(GLFWwindow* window, double x, double y)
{
    std::cout << "x: " << x << " y: " << y << '\n';
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}