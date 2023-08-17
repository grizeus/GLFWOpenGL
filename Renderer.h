#pragma once
#ifdef _WIN32
#include <glad/glad.h>
#elif __linux__
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

using window_ptr = std::shared_ptr<GLFWwindow>;

class renderer
{
public:
	renderer();
	~renderer();

	void create_window(const std::string& title, int width, int height);
	window_ptr get_window();
private:
	window_ptr m_window;
};

