#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ostream>
#include "..\rendering\ShaderLoader.h"

class GLSL_shader {
public:

    GLSL_shader() {
        loc = -1;
        m_handle = -1;
    }
    GLSL_shader(const char* vert, const char* frag) {
        loc = -1;
        m_handle = -1;
        m_handle = load_shader(vert, frag);
    }

    void Use() {
        glUseProgram(m_handle);
    }

    void SetInt(const char* name, const GLint& value) {
        loc = getUniformID(name);
        glUniform1iv(loc, 1, &value);
    }
    void SetUint(const char* name, const GLuint& value) {
        loc = getUniformID(name);
        glUniform1uiv(loc, 1, &value);
    }
    void SetFloat(const char* name, const GLfloat& value) {
        loc = getUniformID(name);
        glUniform1fv(loc, 1, &value);
    }
    void SetVec2(const char* name, const glm::vec2& value) {
        loc = getUniformID(name);
        glUniform2fv(loc, 1, &value[0]);
    }
    void SetVec3(const char* name, const glm::vec3& value) {
        loc = getUniformID(name);
        glUniform3fv(loc, 1, &value[0]);
    }
    void SetVec4(const char* name, const glm::vec4& value) {
        loc = getUniformID(name);
        glUniform4fv(loc, 1, &value[0]);
    }
    void SetMat3(const char* name, const glm::mat3& value) {
        loc = getUniformID(name);
        glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
    }
    void SetMat4(const char* name, const glm::mat4& value) {
        loc = getUniformID(name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
    }

    GLuint GetHandle() { return m_handle; }
    GLuint DeleteShader() {
        glDeleteProgram(m_handle);
        m_handle = -1;
    }
    GLuint CreateShader(const char* vert, const char* frag) {
        if (m_handle != -1)
            throw("delete previous shader first");
        m_handle = load_shader(vert, frag);
    };

private:

    GLuint m_handle;
    GLint loc;

    GLint getUniformID(const char* name) {
        loc = glGetUniformLocation(m_handle, name);
        if (loc >= 0)
            return loc;
        else
            throw("invalid uniform name");
        return loc;
    }
};