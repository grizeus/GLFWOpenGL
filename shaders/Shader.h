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
    void set_mat4(const char* name, const glm::mat4& value);
    inline GLuint get_handle() { return m_handle; }
    void delete_shader();

private:
    GLuint m_handle;
    GLint m_location;

    GLint get_uniform_ID(const char* name);
};
