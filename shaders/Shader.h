#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ostream>
#include "ShaderLoader.h"

class GLSL_shader 
{
public:

    GLSL_shader();
    GLSL_shader(const char* vert, const char* frag);

    void use();
    inline GLuint get_handle() { return m_handle; }
    void delete_shader();

private:
    GLuint m_handle;
};
