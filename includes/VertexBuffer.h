#pragma once

class VertexBuffer{

private:
    unsigned int m_RendererID;

public:
    VertexBuffer(const void *data, unsigned int size);
    void bind()const;
    void unbind()const;
    ~VertexBuffer();
};