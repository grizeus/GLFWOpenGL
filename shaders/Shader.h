#pragma once
#ifdef _WIN32
#include <glad/glad.h>
#elif __linux__
#include <GL/gl.h>
#endif
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
    void create_shader(const char* vert, const char* frag);

private:
    GLuint m_handle;
};
