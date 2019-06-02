#include "Index.h"
#include "Renderer.h"
#include <OpenGL/gl3.h>

Index::Index(const unsigned int* data, unsigned int count) : m_count{count} {
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}

Index::~Index() {
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void Index::bind()const{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void Index::unbind()const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
