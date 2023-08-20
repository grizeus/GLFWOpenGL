#pragma once
#include "events/EventSubscriber.h"
#include "rendering/Renderer.h"

#include <iostream>

class input : public event_subscriber
{
public:
    input(window_ptr window) : m_window(window) { }
    ~input() = default;

    inline void on_event(const event& e) override;
private:
    window_ptr m_window;
};

void input::on_event(const event& e)
{
    if (e.get_type() == etype::key_pressed)
    {
        const key_pressed_event& inside_event = dynamic_cast<const key_pressed_event&>(e);
        if (inside_event.get_key_code() == key_code::ESCAPE) 
            glfwSetWindowShouldClose(m_window.get(), true);
    }
}