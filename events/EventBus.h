#pragma once

#include "EventSubscriber.h"
#include "Event.h"

#include <memory>
#include <unordered_map>
#include <vector>


struct GLFWwindow;

class event_bus
{
public:
	using subscribers_container = std::vector<event_subscriber*>;

	event_bus() = default;
	event_bus(std::shared_ptr<GLFWwindow> window);

	void on_mouse_moved(double x_pos, double y_pos);
	void on_window_resize(int width, int height);
	void on_key_pressed(int key, int scancode, int action, int mods);

private:
	std::unordered_map<etype, subscribers_container> m_subscribers;
};
