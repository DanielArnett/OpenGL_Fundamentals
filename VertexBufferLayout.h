#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include "Renderer.h"

#include <iostream>
#include <vector>

struct VertexBufferLayoutElement
{
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        
        std::cout << "ERROR: Unknown type given for VertexBufferLayoutElement::GetSizeOfType()" << std::endl;
        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
    : m_Stride(0)
    {
    }

    template<typename T>
    void Push(int count)
    {
        T t;
        Push(count, t);
    }

    inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }

private:
    void Push(unsigned int count, float type)
    {
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_Stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
    }

    void Push(unsigned int count, unsigned int type)
    {
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_Stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    void Push(unsigned int count, unsigned char type)
    {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_Stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

private:
    std::vector<VertexBufferLayoutElement> m_Elements;
    unsigned int m_Stride;
};

#endif // defined(VERTEX_BUFFER_LAYOUT)