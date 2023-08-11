#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Callbacks.h"
#include "Utilities.h"
#include "Input.h"
#include "Vertex.h"
#include "DrawDetails.h"
#include "Version.h"
#include "Query.h"
#include "shaders/Shader.h"
#include "rendering/OpenGLDraw.h"
#include "rendering/OpenGLLoader.h"
#include "rendering/ShaderLoader.h"
#include <iostream>
#include <vector>

GLSL_shader* cursor_shader;
GLSL_shader* overlay_shader;

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, extract_version(argv[0]), nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    else
        glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    print_GL_info();

    glfwSetWindowCloseCallback(window, glfw_window_close_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, glfw_mouse_movement_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    std::string vertex_shader = read_to_string("shaders\\2DVertexShader.glsl");
    std::string fragment_shader = read_to_string("shaders\\CursorFragShader.glsl");
    cursor_shader = new GLSL_shader(vertex_shader.c_str(), fragment_shader.c_str());
   
    query_input_attribs(cursor_shader->get_handle());
    query_uniforms(cursor_shader->get_handle());

    fragment_shader = read_to_string("shaders\\SmoothFragShader.glsl");
    overlay_shader = new GLSL_shader(vertex_shader.c_str(), fragment_shader.c_str());
    query_input_attribs(overlay_shader->get_handle());
    query_uniforms(overlay_shader->get_handle());
    overlay_shader->use();
    overlay_shader->set_vec2("uResolution", glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));

    glClearColor(0.3f, 0.3f, 0.65f, 0.f);
    std::vector<draw_strip_details> strip;

    const GLfloat strip_pos_data[] = {
        -1, 1,
        -1, -1,
        1, 1,
        1, -1
    };

    strip.push_back(upload_mesh(strip_pos_data, sizeof(strip_pos_data) / sizeof(strip_pos_data[0])));

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClear(GL_COLOR_BUFFER_BIT);

        overlay_shader->use();
        strip_draw(strip);
        cursor_shader->use();
        strip_draw(strip);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // remove data from GPU
    unload_mesh(strip);
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
