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
    std::string vert_shader = read_to_string("shaders\\vert_transform.glsl");
    std::string frag_shader = read_to_string("shaders\\frag_textured.glsl");
    std::unique_ptr<GLSL_shader> shader = std::make_unique<GLSL_shader>(vert_shader.c_str(), frag_shader.c_str());

    std::shared_ptr<camera> camera_handler = std::make_shared<camera>(shader->get_handle(), renderer_handle.get_width(), renderer_handle.get_height());
    bus.subscribe(camera_handler, etype::window_resize);
    bus.subscribe(camera_handler, etype::key_pressed);
    query_input_attribs(shader->get_handle());
    query_uniforms(shader->get_handle());

    //object renderable_obj("media\\untitled.obj");
	object renderable_obj;
    GLuint texture = load_DDS("media\\template.DDS");
    renderable_obj.set_texture(texture);
    //renderable_obj.upload_textured_mesh(shader->get_handle());

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

	// Two UV coordinatesfor each vertex. They were created with Blender.
	static const GLfloat uv_buffer_data[] = {
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		0.335973f, 1.0f - 0.335903f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
	};

	vec_glfloat vertex(std::begin(vertex_buffer_data), std::end(vertex_buffer_data));
	vec_glfloat uv(std::begin(uv_buffer_data), std::end(uv_buffer_data));
	renderable_obj.set_vertices(vertex);
	renderable_obj.set_uv(uv);
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
