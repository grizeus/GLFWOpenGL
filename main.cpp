#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Callbacks.h"
#include "Utilities.h"
#include "Input.h"
#include "Vertex.h"
#include "Version.h"
#include "Query.h"
#include "rendering/OpenGLDraw.h"
#include "rendering/OpenGLLoader.h"
#include "rendering/ShaderLoader.h"
#include <iostream>
#include <vector>

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

    std::string vertex_shader = read_to_string("shaders\\VertexShader.glsl");
    std::string fragment_shader = read_to_string("shaders\\FragmentShader.glsl");

    unsigned int main_shader = load_shader(vertex_shader.c_str(), fragment_shader.c_str());
    glClearColor(0.3f, 0.3f, 0.9f, 0.f);

    std::vector<draw_details> triangle;
    const float position_data[] = {
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f,
         0.0f,  0.8f, 0.0f
    };

    const float color_data[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    const GLuint elems[] = { 0, 1, 2 };
    triangle.push_back(upload_mesh(position_data, color_data, sizeof(position_data) / sizeof(position_data[0]),
        elems, sizeof(elems) / sizeof(elems[0])));
    
    query_input_attribs(main_shader);
    query_uniforms(main_shader);

    double prev_time = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double current_time = glfwGetTime();
        double dt = current_time - prev_time;
        prev_time = current_time;

        process_input(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(main_shader);
        glm::mat4 final_model_matrix = glm::mat4(1);
        final_model_matrix = glm::translate(final_model_matrix, glm::vec3(sin((float)glfwGetTime()) / 2, cos((float)glfwGetTime()) / 2, 0));
        final_model_matrix = glm::rotate(final_model_matrix, (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f));
        final_model_matrix = glm::scale(final_model_matrix, glm::vec3(.5));
        GLuint location = glGetUniformLocation(main_shader, "uModelMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &final_model_matrix[0][0]);
        draw(triangle);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // remove data from GPU
    unload_mesh(triangle);
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
