#pragma once

#include <functional>
#include <OpenGL/gl3.h>

GLuint CompileShader(GLenum type, const char* source);
GLuint LinkShader(GLuint vertex, GLuint pixel, std::function<void(GLuint)> bind_attribs);
