#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ostream>
#include "..\rendering\ShaderLoader.h"

class GLSL_shader {
public:

    GLSL_shader();
    GLSL_shader(const char* vert, const char* frag);

    void use();

    void set_int(const char* name, const GLint& value);
    void set_uint(const char* name, const GLuint& value);
    void set_float(const char* name, const GLfloat& value);
    void set_vec2(const char* name, const glm::vec2& value);
    void set_vec3(const char* name, const glm::vec3& value);
    void set_vec4(const char* name, const glm::vec4& value);
    void set_mat3(const char* name, const glm::mat3& value);
    void set_mat4(const char* name, const glm::mat4& value);

    inline GLuint get_handle() { return m_handle; }
    void delete_shader();
    GLuint create_shader(const char* vert, const char* frag);

private:

    GLuint m_handle;
    GLint m_location;

    GLint get_uniform_ID(const char* name);
};