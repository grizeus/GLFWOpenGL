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
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
    glfwSetCursorPosCallback(window, glfw_mouse_movement_callback);
    glfwSetKeyCallback(window, glfw_key_callback);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    std::string vert_shade = read_to_string("shaders\\vert_2d.glsl");
    std::string frag_shade = read_to_string("shaders\\frag_base.glsl");
    unsigned int shader = load_shader(vert_shade.c_str(), frag_shade.c_str());

    glClearColor(0.3f, 0.3f, 0.65f, 0.f);
    //std::vector<draw_details> cube;
    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };
    //static const GLfloat g_vertex_buffer_data[] = {
    //-1.0f,-1.0f,-1.0f, // triangle 1 : begin
    //-1.0f,-1.0f, 1.0f,
    //-1.0f, 1.0f, 1.0f, // triangle 1 : end
    //1.0f, 1.0f,-1.0f, // triangle 2 : begin
    //-1.0f,-1.0f,-1.0f,
    //-1.0f, 1.0f,-1.0f, // triangle 2 : end
    //1.0f,-1.0f, 1.0f,
    //-1.0f,-1.0f,-1.0f,
    //1.0f,-1.0f,-1.0f,
    //1.0f, 1.0f,-1.0f,
    //1.0f,-1.0f,-1.0f,
    //-1.0f,-1.0f,-1.0f,
    //-1.0f,-1.0f,-1.0f,
    //-1.0f, 1.0f, 1.0f,
    //-1.0f, 1.0f,-1.0f,
    //1.0f,-1.0f, 1.0f,
    //-1.0f,-1.0f, 1.0f,
    //-1.0f,-1.0f,-1.0f,
    //-1.0f, 1.0f, 1.0f,
    //-1.0f,-1.0f, 1.0f,
    //1.0f,-1.0f, 1.0f,
    //1.0f, 1.0f, 1.0f,
    //1.0f,-1.0f,-1.0f,
    //1.0f, 1.0f,-1.0f,
    //1.0f,-1.0f,-1.0f,
    //1.0f, 1.0f, 1.0f,
    //1.0f,-1.0f, 1.0f,
    //1.0f, 1.0f, 1.0f,
    //1.0f, 1.0f,-1.0f,
    //-1.0f, 1.0f,-1.0f,
    //1.0f, 1.0f, 1.0f,
    //-1.0f, 1.0f,-1.0f,
    //-1.0f, 1.0f, 1.0f,
    //1.0f, 1.0f, 1.0f,
    //-1.0f, 1.0f, 1.0f,
    //1.0f,-1.0f, 1.0f
    //};

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // One color for each vertex. They were generated randomly.
    /*static const GLfloat g_color_buffer_data[] = {
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
    };*/
    /*GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);*/
    //const GLuint elems[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36 };

    //cube.push_back(upload_mesh(g_vertex_buffer_data, g_color_buffer_data, sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]), elems, sizeof(elems) / sizeof(elems[0])));
 
    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glUseProgram(shader);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
        //glEnableVertexAttribArray(0);
        //glEnableVertexAttribArray(1);
        //glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        //glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        //glVertexAttribPointer(
        //    1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        //    3,                                // size
        //    GL_FLOAT,                         // type
        //    GL_FALSE,                         // normalized?
        //    0,                                // stride
        //    (void*)0                          // array buffer offset
        //);
        //glVertexAttribPointer(
        //    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        //    3,                  // size
        //    GL_FLOAT,           // type
        //    GL_FALSE,           // normalized?
        //    0,                  // stride
        //    (void*)0            // array buffer offset
        //);
        //// Draw the triangle !
        //glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        //glDisableVertexAttribArray(0);
        //draw(cube);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // remove data from GPU
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
