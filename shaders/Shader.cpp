#include "Shader.h"

GLSL_shader::GLSL_shader()
{
	m_location = -1;
	m_handle = -1;
}

GLSL_shader::GLSL_shader(const char* vert, const char* frag) 
{
    m_location = -1;
    m_handle = -1;
    m_handle = load_shader(vert, frag);
}

void GLSL_shader::use() 
{
    glUseProgram(m_handle);
}

void GLSL_shader::set_int(const char* name, const GLint& value)
{
    m_location = get_uniform_ID(name);
    glUniform1iv(m_location, 1, &value);
}

void GLSL_shader::set_uint(const char* name, const GLuint& value)
{
    m_location = get_uniform_ID(name);
    glUniform1uiv(m_location, 1, &value);
}

void GLSL_shader::set_float(const char* name, const GLfloat& value)
{
    m_location = get_uniform_ID(name);
    glUniform1fv(m_location, 1, &value);
}

void GLSL_shader::set_vec2(const char* name, const glm::vec2& value)
{
    m_location = get_uniform_ID(name);
    glUniform2fv(m_location, 1, &value[0]);
}

void GLSL_shader::set_vec3(const char* name, const glm::vec3& value)
{
    m_location = get_uniform_ID(name);
    glUniform3fv(m_location, 1, &value[0]);
}

void GLSL_shader::set_vec4(const char* name, const glm::vec4& value)
{
    m_location = get_uniform_ID(name);
    glUniform4fv(m_location, 1, &value[0]);
}

void GLSL_shader::set_mat3(const char* name, const glm::mat3& value)
{
    m_location = get_uniform_ID(name);
    glUniformMatrix3fv(m_location, 1, GL_FALSE, &value[0][0]);
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
}

GLuint GLSL_shader::create_shader(const char* vert, const char* frag)
{
    if (m_handle != -1)
        throw("delete previous shader first");
    m_handle = load_shader(vert, frag);
}

GLint GLSL_shader::get_uniform_ID(const char* name)
{
    m_location = glGetUniformLocation(m_handle, name);
    if (m_location >= 0)
        return m_location;
    else
        throw("invalid uniform name");
    return m_location;
}
