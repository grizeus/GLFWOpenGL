#pragma once
#include "KeyCodes.h"

#include <ostream>
#include <sstream>

enum class etype
{
	none = 0,
	window_close, window_resize,
	app_tick, app_update, app_render,
	key_pressed, key_released, key_typed,
	mouse_button_pressed, mouse_button_released, mouse_moved, mouse_scrolled
};

class event
{
public:
	event() = default;
	virtual ~event() = default;
	virtual std::string to_string() const = 0;
};

class window_event : public event
{
public:
	inline int get_width() const { return m_width; }
	inline int get_height() const { return m_height; }
protected:
	window_event(const int width, const int height)
		: m_width(width), m_height(height)
	{}

	int m_width;
	int m_height;
};

class mouse_event : public event
{
public:
	inline double get_x() const { return m_x; }
	inline double get_y() const { return m_y; }

protected:
	mouse_event(const double x, const double y)
		: m_x(x), m_y(y)
	{}

	double m_x;
	double m_y;
};

class mouse_moved_event : public mouse_event
{
public:

	mouse_moved_event(const double x,  const double y)
		: mouse_event(x, y)
	{}

	// TODO
	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "mouse_moved_event on: " << m_x << ":" << m_y ;
		return ss.str();
	}
private:
	double m_x;
	double m_y;
};

class key_event : public event
{
public:
	inline key_code get_key_code() const { return m_key_code; }
protected:
	key_event(const key_code code)
		: m_key_code(code)
	{}

	key_code m_key_code;
};

class key_pressed_event : public key_event
{
public:
	key_pressed_event(const key_code code, bool is_repeat = false)
		: key_event(code), m_is_repeat(is_repeat)
	{}

	inline bool is_repeat() const { return m_is_repeat; }
	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "key_pressed_event: " << m_key_code << " (repeat=" << m_is_repeat << ")";
		return ss.str();
	}
private:
	bool m_is_repeat;
};

class key_released_event : public key_event
{
public:
	key_released_event(const key_code code)
		: key_event(code)
	{}

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "key_released_event: " << m_key_code;
		return ss.str();
	}
};

class key_typed_event : public key_event
{
public:
	key_typed_event(const key_code code)
		: key_event(code)
	{}

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "key_typed_event: " << m_key_code;
		return ss.str();
	}
};

class window_resize_event : public window_event
{
public:
	window_resize_event(int width, int height)
		: window_event(width, height)
	{ }

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "window_resize_event to: " << m_width << ":" << m_height;
		return ss.str();
	}
};
inline std::ostream& operator<<(std::ostream& os, const event& e)
{
	return os << e.to_string();
}
