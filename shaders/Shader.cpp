#include "Shader.h"

GLSL_shader::GLSL_shader()
{
	m_handle = -1;
    m_location = -1;
}

GLSL_shader::GLSL_shader(const char* vert, const char* frag) 
{
    m_handle = -1;
    m_location = -1;
    m_handle = load_shader(vert, frag);
}

void GLSL_shader::use() 
{
    glUseProgram(m_handle);
}

void GLSL_shader::set_mat4(const char* name, const glm::mat4& value)
{
    m_location = get_uniform_ID(name);
    glUniformMatrix4fv(m_location, 1, GL_FALSE, &value[0][0]);
}

void GLSL_shader::delete_shader()
{
    glDeleteProgram(m_handle);
    m_handle = -1;
    m_location = -1;
}

GLint GLSL_shader::get_uniform_ID(const char* name)
{
    m_location = glGetUniformLocation(m_handle, name);
    return m_location;
}