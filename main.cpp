#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"
#include "events/EventBus.h"
#include "rendering/Camera.h"
#include "rendering/Renderer.h"
#include "object/Object.h"
#include "utilities/Utilities.h"
#include "utilities/Version.h"
#include "utilities/Query.h"
#include "shaders/ShaderLoader.h"
#include "shaders/Shader.h"
#include <iostream>
#include <vector>


int main(int argc, char** argv)
{
    renderer renderer_handle;
    renderer_handle.create_window(extract_version(argv[0]));

    print_GL_info();
    GLFWwindow* window = renderer_handle.get_window().get();
    
    event_bus bus(renderer_handle.get_window());
    sub_ptr input_handler = std::shared_ptr<event_subscriber>(new input (renderer_handle.get_window()));
    bus.subscribe(input_handler, etype::key_pressed);
    std::string vert_shader = read_to_string("shaders\\vert_2d.glsl");
    std::string frag_shader = read_to_string("shaders\\frag_base.glsl");
    std::shared_ptr<GLSL_shader> shader = std::make_shared<GLSL_shader>(vert_shader.c_str(), frag_shader.c_str());

    std::shared_ptr<camera> camera_handler(new camera(shader->get_handle(), renderer_handle.get_width(), renderer_handle.get_height()));
    bus.subscribe(camera_handler, etype::window_resize);
    bus.subscribe(camera_handler, etype::key_pressed);
    query_input_attribs(shader->get_handle());
    query_uniforms(shader->get_handle());

    object suz("media\\untitled.obj");
    suz.set_texture(suz.load_BMP("media//numbers.bmp"));
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
    
    vec_glfloat color_data(std::begin(color_buffer_data), std::end(color_buffer_data));
    suz.set_colors(color_data);
    suz.upload_textured_mesh(shader->get_handle());
    
    double last_time = static_cast<float>(glfwGetTime());
    while (!glfwWindowShouldClose(window))
    {
        // set time ticks
        double cur_time = static_cast<double>(glfwGetTime());
        double delta_time = cur_time - last_time;
        last_time = cur_time;
        camera_handler->set_delta_time(delta_time);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader->use();
        
        camera_handler->on_render();
        suz.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
      
    return 0;
}
