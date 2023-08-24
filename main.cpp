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

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


int main(int argc, char** argv)
{
    renderer renderer_handle;
    renderer_handle.create_window(extract_version(argv[0]));

    print_GL_info();
    GLFWwindow* window = renderer_handle.get_window().get();
    
    event_bus bus(renderer_handle.get_window());
    sub_ptr input_handler = std::shared_ptr<event_subscriber>(new input (renderer_handle.get_window()));
    bus.subscribe(input_handler, etype::key_pressed);
    std::string vert_shader = read_to_string("shaders\\vert_transform.glsl");
    std::string frag_shader = read_to_string("shaders\\frag_textured.glsl");
    std::unique_ptr<GLSL_shader> shader = std::make_unique<GLSL_shader>(vert_shader.c_str(), frag_shader.c_str());

    std::shared_ptr<camera> camera_handler = std::make_shared<camera>(shader->get_handle(), renderer_handle.get_width(), renderer_handle.get_height());
    bus.subscribe(camera_handler, etype::window_resize);
    bus.subscribe(camera_handler, etype::key_pressed);
    query_input_attribs(shader->get_handle());
    query_uniforms(shader->get_handle());

    object renderable_obj("media\\numbers.obj");
    renderable_obj.set_texture(load_DDS("media\\template.DDS"));
	renderable_obj.upload_textured_mesh(shader->get_handle());

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
        renderable_obj.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
      
    return 0;
}
