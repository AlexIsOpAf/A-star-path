#pragma once
#include <vector>
#include <OpenGL/gl3.h>
#include "Renderer.h"

struct LayoutElement{

    unsigned int type;
    unsigned int count;
    unsigned char normalised;

    static unsigned int get_size_of_type(unsigned int type){
        switch(type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
        ASSERT(false);
    }

};

class VertexBufferLayout{
private:
    std::vector<LayoutElement> m_elements;
    unsigned int m_stride;

public:
    VertexBufferLayout();

    template <typename T>
    void push(unsigned int count);
    inline const std::vector<LayoutElement>& get_elements() const {return m_elements;}
    unsigned int get_stride() const {return m_stride;}
    ~VertexBufferLayout();
};

