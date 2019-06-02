#include <iostream>
#include "Renderer.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GL_log_call(const char* function, const char *file, int line) {
    
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error " << error << " ]" << std::endl;
        return false;
    }
    return true;
}