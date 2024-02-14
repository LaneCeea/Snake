#include "Renderer.h"

#include <Renderer/RendererAPI.h>

#include <array>

RendererData Renderer::s_Data;

void Renderer::Init() {
    {
        // Create m_SquareVA
        constexpr std::size_t _StrideCount = 5;
        const std::array<float, _StrideCount * 4> _Verticies = {
            // Positions       |  TexCoord                   |
            -0.5f, -0.5f,  0.0f,  0.0f,  0.0f, // 0
             0.5f, -0.5f,  0.0f,  1.0f,  0.0f, // 1
             0.5f,  0.5f,  0.0f,  1.0f,  1.0f, // 2
            -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, // 3
        };

        const std::array<std::uint32_t, 6> _Indicies = {
            0, 1, 2, 2, 3, 0,
        };

        s_Data.SquareVao.Init(_Verticies, _Indicies,
            VertexLayout{
                ShaderDataType::Float3,
                ShaderDataType::Float2,
            });
    }
}

void Renderer::DrawSquare() {
    RendererAPI::Draw(s_Data.SquareVao);
}
