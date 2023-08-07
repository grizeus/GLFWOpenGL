#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Callbacks.h"
#include "Utilities.h"
#include "Input.h"
#include "Vertex.h"
#include "Version.h"
#include "rendering/OpenGLDraw.h"
#include "rendering/OpenGLLoader.h"
#include "rendering/ShaderLoader.h"
#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    print_GL_info();
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load texture raw data
    int width, height, nr_col_channels;
    unsigned char* text_data = stbi_load("media\container.jpg", &width, &height, &nr_col_channels, 0);

    // bound raw data to texture
    if (text_data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, text_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        printf("Failed to load texture\n");

    stbi_image_free(text_data);

    std::vector<draw_details> container;
    {
        std::vector<text_vertex> obj_pts;
        obj_pts.emplace_back(0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
        obj_pts.emplace_back(0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
        obj_pts.emplace_back(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        obj_pts.emplace_back(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

        std::vector<uint32_t> elem = { 0, 1, 2, 3 };

        container.push_back(upload_mesh(obj_pts, elem));
    }

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    const char* vertex_shader =
        "#version 430 core                      \n"
        "layout (location = 0) in vec3 m_pos;   \n"
        "layout (location = 1) in vec3 m_col;   \n"
        "out vec3 our_color;                    \n"
        "void main(){                           \n"
        "  gl_Position = vec4(m_pos, 1.0);      \n"
        "  our_color = m_col;                   \n"
        "}";
    const char* fragment_shader =
        "#version 430 core                      \n"
        "out vec4 frag_color;                   \n"
        "in vec3 our_color;                     \n"
        "void main() {                          \n"
        "  frag_color = vec4(our_color, 1.f);   \n"
        "}";

    unsigned int main_shader = load_shader(vertex_shader, fragment_shader);
    glClearColor(.2f, .2f, .6f, .0f);
    std::vector<draw_details> our_triangle;
    {
        std::vector<triangle_vertex> obj_pts;
        obj_pts.emplace_back(.5f, -.5f, 0.f, 1.f, 0.f, 0.f);
        obj_pts.emplace_back(-.5f, -.5f, 0.f, 0.f, 1.f, 0.f);
		obj_pts.emplace_back(0.f, .5f, 0.f, 0.f, 0.f, 1.f);

		std::vector<uint32_t> elem = { 0, 1, 2 };

		// UPLOAD DATA TO GRAPHICS CARD
		our_triangle.push_back(upload_mesh(obj_pts, elem));
    }

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(main_shader);
        draw(our_triangle);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // remove data from GPU
    unload_mesh(our_triangle);
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
