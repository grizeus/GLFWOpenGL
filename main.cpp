#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Callbacks.h"
#include "Utilities.h"
#include "Input.h"
#include "Vertex.h"
#include "rendering/OpenGLDraw.h"
#include "rendering/OpenGLLoader.h"
#include "rendering/ShaderLoader.h"
#include <iostream>
#include <vector>
#include <random>

int main(int argc, char** argv)
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    // init OpenGL
    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();
    if (!glfwInit())
    {   
        std::cout << "GLFW failed to initialize. Quitting\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, extract_version(argv[0]), nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    const char* vertex_shader =
        "#version 330 core                      \n"
        "layout (location = 0) in vec3 m_pos;   \n"
        "layout (location = 1) in vec3 m_col;   \n"
        "out vec3 our_color;                    \n"
        "void main(){                           \n"
        "  gl_Position = vec4(m_pos, 1.0);      \n"
        "  our_color = m_col;                   \n"
        "}";
    const char* fragment_shader =
        "#version 330 core                      \n"
        "out vec4 frag_color;                   \n"
        "in vec3 our_color;                     \n"
        "void main() {                          \n"
        "  frag_color = vec4(our_color, 1.f);   \n"
        "}";
    unsigned int main_shader = load_shader(vertex_shader, fragment_shader);
    glClearColor(.2f, .2f, .6f, .0f);
    std::vector<draw_details> our_draw_details;
    {
        std::vector<vertex> obj_pts;
        obj_pts.emplace_back(.5f, -.5f, 0.f, 1.f, 0.f, 0.f);
        obj_pts.emplace_back(-.5f, -.5f, 0.f, 0.f, 1.f, 0.f);
		obj_pts.emplace_back(0.f, .5f, 0.f, 0.f, 0.f, 1.f);

		std::vector<uint32_t> elem = { 0, 1, 2 };

		// UPLOAD DATA TO GRAPHICS CARD
		our_draw_details.push_back(upload_mesh(obj_pts, elem));
    }

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(main_shader);
        draw(our_draw_details);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // remove data from GPU
    unload_mesh(our_draw_details);
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
