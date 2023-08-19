#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

using window_ptr = std::shared_ptr<GLFWwindow>;

class renderer
{
public:
	renderer();
	~renderer();

	void create_window(const std::string& title);
	window_ptr get_window() const;
	inline int get_width() const { return m_width; }
	inline int get_height() const { return m_height; }
private:
	window_ptr m_window;
	const int m_width = 800;
	const int m_height = 600;
};

