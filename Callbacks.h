#pragma once
#include <GLFW/glfw3.h>
#include <cstdio>
#include "Utilities.h"

static void glfw_error_callback(int error, const char* description)
{
    write_log(description);
    throw("glfw error");
}

static void glfw_window_close_callback(GLFWwindow* window)
{
    write_log("Window closed\n");
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::string size = "Window resized to " + std::to_string(width) + "x" + std::to_string(height) + " \n";
    write_log(size.c_str());
    glViewport(0, 0, width, height);
}
