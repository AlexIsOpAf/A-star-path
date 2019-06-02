#pragma once

#include <OpenGL/gl3.h>
#include <signal.h>

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GL_log_call(#x, __FILE__, __LINE__))

void GLClearError();
bool GL_log_call(const char* function, const char* file, int line);