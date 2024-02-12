#ifndef RENDERER_VERTEXARRAY_H_
#define RENDERER_VERTEXARRAY_H_

#include <Renderer/VertexLayout.h>

#include <glad/glad.h>

#include <cstdint>

class VertexArray {
public:
    VertexArray() = default;

    template<std::size_t _Size1, std::size_t _Size2>
    VertexArray(
        const std::array<float, _Size1>& _Verticies,
        const std::array<std::uint32_t, _Size2>& _Indicies,
        const VertexLayout& _Layout) {
        Init(_Verticies.data(), _Verticies.size(), _Indicies.data(), _Indicies.size(), _Layout);
    }

    ~VertexArray();

    void Init(
        const float* _Verticies, std::size_t _VerticiesSize,
        const std::uint32_t* _Indicies, std::size_t _IndiciesSize,
        const VertexLayout& _Layout);

    void Clear();

    void Bind() const;
    void Unbind() const;

    constexpr std::uint16_t IndexCount() const { return m_IndexCount; }

private:
    std::uint32_t m_ReferenceID;
    std::uint32_t m_IndexCount;
};

#endif // !RENDERER_VERTEXARRAY_H_
