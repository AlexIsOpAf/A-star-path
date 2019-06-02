#pragma once

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


class VertexArray{

private:
    unsigned int m_renderedID;

public:
    VertexArray();
    ~VertexArray();

    void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void bind() const;
    void unbind()const;


};