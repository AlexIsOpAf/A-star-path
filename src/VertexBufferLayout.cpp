#include "VertexBufferLayout.h" 


VertexBufferLayout::VertexBufferLayout() : m_stride{0} {

}

template <typename T>
void VertexBufferLayout::push(unsigned int count){
    
}

template<>
void VertexBufferLayout::push<float>(unsigned int count){
    m_elements.push_back({count,GL_FLOAT,  GL_FALSE});
    m_stride += count * LayoutElement::get_size_of_type(GL_FLOAT);
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
    m_elements.push_back({count,GL_UNSIGNED_INT,  GL_FALSE});
    m_stride += count * LayoutElement::get_size_of_type(GL_UNSIGNED_INT);
}
template <>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
    m_elements.push_back({count,GL_UNSIGNED_BYTE,  GL_TRUE});
    m_stride += count * LayoutElement::get_size_of_type(GL_UNSIGNED_BYTE);
}

VertexBufferLayout::~VertexBufferLayout(){


}
