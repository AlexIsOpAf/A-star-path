#pragma once

class Index{

private:
    unsigned int m_RendererID;
    unsigned int m_count;

public:
    Index(const unsigned int *data, unsigned int count);
    void bind() const;
    void unbind()const;
    ~Index();
};