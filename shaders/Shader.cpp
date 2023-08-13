#include "Shader.h"

GLSL_shader::GLSL_shader()
{
	m_handle = -1;
}

GLSL_shader::GLSL_shader(const char* vert, const char* frag) 
{
    m_handle = -1;
    m_handle = load_shader(vert, frag);
}

void GLSL_shader::use() 
{
    glUseProgram(m_handle);
}

void GLSL_shader::delete_shader()
{
    glDeleteProgram(m_handle);
    m_handle = -1;
}

void GLSL_shader::create_shader(const char* vert, const char* frag)
{
    if (m_handle != -1)
        throw("delete previous shader first");
    m_handle = load_shader(vert, frag);
}