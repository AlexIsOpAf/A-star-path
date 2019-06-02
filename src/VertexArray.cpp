#include "VertexArray.h" 
#include "Renderer.h"

VertexArray::VertexArray() {

    GLCall(glGenVertexArrays(1, &m_renderedID));
    GLCall(glBindVertexArray(m_renderedID));
}

void VertexArray::bind()const{
    GLCall(glBindVertexArray(m_renderedID));
}

void VertexArray::unbind()const{
    GLCall(glBindVertexArray(0));
}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {

    bind();
    vb.bind();
    const auto& elements = layout.get_elements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++) {

        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i,element.type ,element.count, element.normalised,layout.get_stride(), (const void*) offset));
        offset += element.count * LayoutElement::get_size_of_type(element.type);
    }

}

VertexArray::~VertexArray(){
    GLCall(glDeleteVertexArrays(1, &m_renderedID));
}

