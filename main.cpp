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

std::unique_ptr<GLSL_shader> cursor_shader;
std::unique_ptr<GLSL_shader> demo_shader;

// camera vars
float FOV = glm::radians(45.f);
float NEAR = .1f;
float FAR = 3000.f;

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

    std::string vertex_shader = read_to_string("shaders\\vert_2d.glsl");
    std::string fragment_shader = read_to_string("shaders\\frag_cursor.glsl");
    cursor_shader = std::make_unique<GLSL_shader>(vertex_shader.c_str(), fragment_shader.c_str());
   
    query_input_attribs(cursor_shader->get_handle());
    query_uniforms(cursor_shader->get_handle());
    cursor_shader->use();
    cursor_shader->set_float("uRadius", 16);

    vertex_shader = read_to_string("shaders\\vert_3d.glsl");
    fragment_shader = read_to_string("shaders\\frag_demo.glsl");
    demo_shader = std::make_unique<GLSL_shader>(vertex_shader.c_str(), fragment_shader.c_str());
    query_input_attribs(demo_shader->get_handle());
    query_uniforms(demo_shader->get_handle());
    demo_shader->use();
    demo_shader->set_vec2("uResolution", glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));

    float ASPECT_RATIO = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
    demo_shader->set_mat4("uProjectionMatrix", glm::perspective(FOV, ASPECT_RATIO, NEAR, FAR));
    glm::mat4 model_matrix(1.f);
    model_matrix = glm::translate(model_matrix, glm::vec3(0, 0, -10)); // make camera smol
    demo_shader->set_mat4("uModelMatrix", model_matrix);
    glm::mat4 view_matrix(1);
    demo_shader->set_mat4("uViewMatrix", view_matrix);

    glClearColor(0.3f, 0.3f, 0.65f, 0.f);
    std::vector<draw_strip_details> strip;

    const GLfloat strip_pos_data[] = {
        -1, 1,
        -1, -1,
        1, 1,
        1, -1
    };

    strip.push_back(upload_mesh(strip_pos_data, sizeof(strip_pos_data) / sizeof(strip_pos_data[0])));

    double prev_time = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double cur_time = glfwGetTime();
        double delta = cur_time - prev_time;
        prev_time = cur_time;

        process_input(window);
        glClear(GL_COLOR_BUFFER_BIT);

        static double accum_time = 0;
        accum_time += delta;

        demo_shader->use();
        demo_shader->set_float("uRunTime", static_cast<const GLfloat>(accum_time));
        model_matrix = glm::rotate(model_matrix, glm::radians((float)(delta * 100)), glm::vec3(0, 1, 0));
        demo_shader->set_mat4("uModelMatrix", model_matrix);
        strip_draw(strip);

        // cursor draw
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
