#include "Renderer.h"
#include "../utilities/Utilities.h"

#include <stdexcept>

renderer::renderer()
    :m_window(nullptr)
{
    // init OpenGL
    glfwInit();
    if (!glfwInit())
    {
        throw std::runtime_error("GLFW failed to initialize");
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

renderer::~renderer()
{
    glfwDestroyWindow(m_window.get());
    glfwTerminate();
}


void renderer::create_window(const std::string& title)
{
    // create window
    m_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, nullptr), glfwDestroyWindow);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    else
        glfwMakeContextCurrent(m_window.get());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    
    glViewport(0, 0, m_width, m_height);
    
    glClearColor(0.3f, 0.3f, 0.65f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

window_ptr renderer::get_window() const
{
	return m_window;
}
