#pragma once
#include <glad/glad.h>
#include <vector>

inline GLuint load_shader(const char* vertex_shader, const char* fragment_shader) {

	// Create the shaders
	GLuint vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint result = GL_FALSE;
	int info_log_length;

	// Compile Vertex Shader
	glShaderSource(vertex_shader_ID, 1, &vertex_shader, NULL);
	glCompileShader(vertex_shader_ID);

	// Check Vertex Shader
	glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertex_shader_ID, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0) {
		std::vector<char> vertex_shader_error_message(info_log_length + 1);
		glGetShaderInfoLog(vertex_shader_ID, info_log_length, NULL, &vertex_shader_error_message[0]);
		printf("%s\n", &vertex_shader_error_message[0]);
	}

	// Compile Fragment Shader
	glShaderSource(fragment_shader_ID, 1, &fragment_shader, NULL);
	glCompileShader(fragment_shader_ID);

	// Check Fragment Shader
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragment_shader_ID, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0) {
		std::vector<char> fragment_shader_error_message(info_log_length + 1);
		glGetShaderInfoLog(fragment_shader_ID, info_log_length, NULL, &fragment_shader_error_message[0]);
		printf("%s\n", &fragment_shader_error_message[0]);
	}

	// Link the program
	GLuint program_ID = glCreateProgram();
	glAttachShader(program_ID, vertex_shader_ID);
	glAttachShader(program_ID, fragment_shader_ID);
	glLinkProgram(program_ID);

	// Check the program
	glGetProgramiv(program_ID, GL_LINK_STATUS, &result);
	glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0) {
		std::vector<char> program_error_message(info_log_length + 1);
		glGetProgramInfoLog(program_ID, info_log_length, NULL, &program_error_message[0]);
		printf("%s\n", &program_error_message[0]);
	}

	glDeleteShader(vertex_shader_ID);
	glDeleteShader(fragment_shader_ID);

	glDetachShader(program_ID, vertex_shader_ID);
	glDetachShader(program_ID, fragment_shader_ID);

	return program_ID;
}