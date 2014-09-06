#include "GLUtils.h"

#include <iostream>

GLuint CompileShader(GLenum type, const char* source) {
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint error;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &error);
	if (error == GL_FALSE) {
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		
		std::string log(length, ' ');
		glGetShaderInfoLog(shader, length, NULL, &log[0]);
		
		std::cerr << log << std::endl;

		return 0;
	}

	return shader;
}

GLuint LinkShader(GLuint vertex, GLuint fragment, std::function<void(GLuint)> bind_attribs) {
	GLuint program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	
	if (bind_attribs) {
		bind_attribs(program);
	}

	glLinkProgram(program);

	GLint error;
	glGetProgramiv(program, GL_LINK_STATUS, &error);
	if (error == GL_FALSE) {
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		std::string log(length, ' ');
		glGetProgramInfoLog(program, length, NULL, &log[0]);

		std::cerr << log << std::endl;
		
		return 0;
	}
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}