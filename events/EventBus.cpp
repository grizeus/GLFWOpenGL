#include "EventBus.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

namespace
{
	inline void error_callback(int error, const char* description)
	{
	}
	inline void window_close_callback(GLFWwindow* window)
	{
		event_bus* handler = reinterpret_cast<event_bus*>(glfwGetWindowUserPointer(window));
		handler->on_window_closed();
	}
	inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		event_bus* handler = reinterpret_cast<event_bus*>(glfwGetWindowUserPointer(window));
		handler->on_window_resize(width, height);
	}
	inline void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos)
	{
		event_bus* handler = reinterpret_cast<event_bus*>(glfwGetWindowUserPointer(window));
		handler->on_mouse_moved(x_pos, y_pos);
	}
	inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		event_bus* handler = reinterpret_cast<event_bus*>(glfwGetWindowUserPointer(window));
		handler->on_key_pressed(key, scancode, action, mods);
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

void event_bus::on_mouse_moved(double x_pos, double y_pos)
{
	std::cout << "Mouse moved to " << x_pos << ":" << y_pos << std::endl;
	auto subscribers = m_subscribers.find(etype::mouse_moved);
	if (subscribers != m_subscribers.end())
	{
		mouse_moved_event e(x_pos, y_pos);
		for (auto& sub : subscribers->second)
			sub->on_event(e);
	}
}

void event_bus::on_window_resize(int width, int height)
{
	std::cout << "Window resize to" << width << ":" << height << std::endl;
	auto subscribers = m_subscribers.find(etype::window_resize);
	if (subscribers != m_subscribers.end())
	{
		window_resize_event e(width, height);
		for (auto& sub : subscribers->second)
			sub->on_event(e);
	}
}

void event_bus::on_window_closed()
{
	std::cout << "Window was closed" << std::endl;
	auto subscribers = m_subscribers.find(etype::window_resize);
	if (subscribers != m_subscribers.end())
	{
		window_closed_event e;
		for (auto& sub : subscribers->second)
			sub->on_event(e);
	}
}

void event_bus::on_key_pressed(int key, int scancode, int action, int mods)
{
	std::cout << "Key pressed with code: " << scancode << std::endl;
	auto subscribers = m_subscribers.find(etype::window_resize);
	if (subscribers != m_subscribers.end())
	{
		key_pressed_event e(static_cast<key_code>(scancode));
		for (auto& sub : subscribers->second)
			sub->on_event(e);
	}
}
