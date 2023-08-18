#include "EventBus.h"

#include <GLFW/glfw3.h>
#include <iostream>


namespace
{
	inline void error_callback(int error, const char* description)
	{
	}
	inline void window_close_callback(GLFWwindow* window)
	{
	}
	inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		event_bus* handler = reinterpret_cast<event_bus*>(glfwGetWindowUserPointer(window));
		//glViewport(0, 0, width, height);
	}
	inline void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos)
	{
		event_bus* handler = reinterpret_cast<event_bus*>(glfwGetWindowUserPointer(window));
		handler->on_mouse_moved(x_pos, y_pos);
	}
	inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
	}
	
}

event_bus::event_bus(std::shared_ptr<GLFWwindow> window)
{
    glfwSetWindowUserPointer(window.get(), this);
	glfwSetErrorCallback(error_callback);
	glfwSetWindowCloseCallback(window.get(), window_close_callback);
	glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);
	glfwSetKeyCallback(window.get(), key_callback);
	glfwSetCursorPosCallback(window.get(), cursor_position_callback);
}

void event_bus::on_mouse_moved(double xpos, double ypos)
{
	std::cout << "Mouse moved to " << xpos << ":" << ypos << std::endl;
	auto subscribers = m_subscribers.find(etype::mouse_moved);
	if (subscribers != m_subscribers.end())
	{
		//do stuff
	}
}
