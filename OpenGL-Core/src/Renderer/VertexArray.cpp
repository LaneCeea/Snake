#include "VertexArray.h"

VertexArray::~VertexArray() {
    Clear();
}

void VertexArray::Init(
    const float* _Verticies, std::size_t _VerticiesSize,
    const std::uint32_t* _Indicies, std::size_t _IndiciesSize,
    const VertexLayout& _Layout) {

    glGenVertexArrays(1, &m_ReferenceID);
    glBindVertexArray(m_ReferenceID);
        
    std::uint32_t _Vbo = 0;
    glGenBuffers(1, &_Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _VerticiesSize, _Verticies, GL_STATIC_DRAW);

    std::uint32_t _Ebo = 0;
    glGenBuffers(1, &_Ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * _IndiciesSize, _Indicies, GL_STATIC_DRAW);
    m_IndexCount = static_cast<std::uint32_t>(_IndiciesSize);

    std::uint32_t _Index = 0;
    std::int32_t _Stride = static_cast<std::int32_t>(_Layout.Stride());
    std::size_t _Offset = 0;
    for (const auto& _Type : _Layout) {
        glEnableVertexAttribArray(_Index);
        glVertexAttribPointer(
            _Index,
            VertexLayout::GetElementComponentCount(_Type),
            VertexLayout::GetElementGLType(_Type),
            GL_FALSE,
            _Stride,
            (const void*)_Offset);
        ++_Index;
        _Offset += VertexLayout::GetElementSize(_Type);
    }
    glBindVertexArray(0);
}

void VertexArray::Clear() {
    glDeleteVertexArrays(1, &m_ReferenceID);
    m_ReferenceID = 0;
}

void VertexArray::Bind() const {
    glBindVertexArray(m_ReferenceID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}
