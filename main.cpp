#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Callbacks.h"
#include "Utilities.h"
#include "Renderer.h"
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

int main(int argc, char** argv)
{
    glfwSetErrorCallback(glfw_error_callback);
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    renderer renderer;
    renderer.create_window(extract_version(argv[0]), WINDOW_WIDTH, WINDOW_HEIGHT);

    print_GL_info();

    glfwSetWindowCloseCallback(renderer.get_window().get(), glfw_window_close_callback);
    glfwSetFramebufferSizeCallback(renderer.get_window().get(), glfw_framebuffer_size_callback);
    glfwSetCursorPosCallback(renderer.get_window().get(), glfw_mouse_movement_callback);
    glfwSetKeyCallback(renderer.get_window().get(), glfw_key_callback);

    // shaders
    std::shared_ptr<GLSL_shader> shader;
    std::string vert_shader = read_to_string("shaders\\vert_2d.glsl");
    std::string frag_shader = read_to_string("shaders\\frag_base.glsl");
    try {
        shader = std::make_shared<GLSL_shader>(vert_shader.c_str(), frag_shader.c_str());
    }
    catch (const std::exception& ex) {
        write_log(ex.what());
    }
    GLuint MatrixID = glGetUniformLocation(shader->get_handle(), "MVP");


    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    constexpr float ASPECT_RATIO = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
    constexpr float FOV = glm::radians(45.0f);
    constexpr float NEAR = 0.1f;
    constexpr float FAR = 100.0f;
    glm::mat4 Projection = glm::perspective(FOV, ASPECT_RATIO, NEAR, FAR);

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, -3), // Camera is at (4,3,-3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

    std::vector<draw_details> cube;
    
    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f
    };
   
    // One color for each vertex. They were generated randomly.
    static const GLfloat color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };
    std::vector<GLfloat> vertex_data(std::begin(vertex_buffer_data), std::end(vertex_buffer_data));
    std::vector<GLfloat> color_data(std::begin(color_buffer_data), std::end(color_buffer_data));
    cube.push_back(upload_mesh(vertex_data, color_data));

    GLFWwindow* window = renderer.get_window().get();
    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //shader->use();
        
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        draw(cube);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // remove data from GPU
    unload_mesh(cube);

    return 0;
}
