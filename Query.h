﻿#pragma once
#include <glad/glad.h>
#include <vector>
#include <stdio.h>
#include <iostream>

const char* get_type_string(GLenum type) 
{
    switch (type) {
    case GL_FLOAT:
        return "float";
    case GL_FLOAT_VEC2:
        return "vec2";
    case GL_FLOAT_VEC3:
        return "vec3";
    case GL_FLOAT_VEC4:
        return "vec4";
    case GL_DOUBLE:
        return "double";
    case GL_INT:
        return "int";
    case GL_UNSIGNED_INT:
        return "unsigned int";

    case GL_INT_VEC2:
        return "ivec2";
    case GL_INT_VEC3:
        return "ivec3";
    case GL_INT_VEC4:
        return "ivec4";
    case GL_SAMPLER_2D:
        return "sampler 2d";
    case GL_SAMPLER_CUBE:
        return "sampler cube";

    case GL_BOOL:
        return "bool";
    case GL_FLOAT_MAT2:
        return "mat2";
    case GL_FLOAT_MAT3:
        return "mat3";
    case GL_FLOAT_MAT4:
        return "mat4";
    case GL_TRUE:
        return "true";
    case GL_FALSE:
        return "false";

    default:
        return "?";
    }

}

inline void query_input_attribs(const GLuint& handle) {
    printf("-----ATTRIBUTES(shaderprog:%i)-----\n", handle);
    // method 1
    GLint num_attribs;
    glGetProgramInterfaceiv(handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &num_attribs);
    printf("Active Inputs(%i):\n", num_attribs);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };
    for (int i = 0; i < num_attribs; ++i) {
        GLint results[3];
        glGetProgramResourceiv(handle, GL_PROGRAM_INPUT, i, 3, properties, 3, NULL, results);

        GLint nameBufSize = results[0] + 1;
        char* name = new char[nameBufSize];
        glGetProgramResourceName(handle, GL_PROGRAM_INPUT, i, nameBufSize, NULL, name);
        printf("%-5d %s (%s)\n", results[2], name, get_type_string(results[1]));
        delete[] name;
    }
}