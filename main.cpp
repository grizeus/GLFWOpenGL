#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    const char* vertex_shader =
        "#version 430 core                         \n"
        "layout(location = 0) in vec3 vertPos;     \n"
        "layout(location = 1) in vec3 vertColor;   \n"
        "layout(location = 0) out vec4 fragColor;  \n"
        "void main(){                              \n"
        "  fragColor = vec4(vertColor, 1.0);       \n"
        "  gl_Position = vec4(vertPos, 1.0);       \n"
        "}";

    const char* fragment_shader =
        "#version 430 core                          \n"
        "layout(location = 0) in vec4 fragColor;    \n"
        "out vec4 color;                            \n"
        "void main() {                              \n"
        "  color = fragColor;                       \n"
        "}";

    unsigned int main_shader = load_shader(vertex_shader, fragment_shader);
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

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(main_shader);
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
