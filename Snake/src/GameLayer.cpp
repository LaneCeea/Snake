#include "GameLayer.h"

#include <ImGui/imgui.h>
#include <Renderer/RendererAPI.h>
#include <Renderer/VertexArray.h>

#include <array>
#include <cmath>

namespace Snake {

GameLayer::GameLayer() : 
    Layer("Snake::GameLayer"),
    m_SquareVA(0), m_FlatColorShader() {
}

GameLayer::~GameLayer() {

}

void GameLayer::OnAttach() {
    m_GlobalTimer.Start();
    {
        // Create m_SquareVA
        constexpr std::size_t _StrideCount = 7;
        const std::array<float, _StrideCount * 4> _Verticies = {
            // Positions       |  Colors                   |
            -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, // 0
             0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f, // 1
             0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f, // 2
            -0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  1.0f,  1.0f, // 3
        };

        const std::array<std::uint32_t, 6> _Indicies = {
            0, 1, 2, 2, 3, 0,
        };

        glGenVertexArrays(1, &m_SquareVA);
        glBindVertexArray(m_SquareVA);

        std::uint32_t _Vbo = 0;
        glGenBuffers(1, &_Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _Vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _Verticies.size(), _Verticies.data(), GL_STATIC_DRAW);

        std::uint32_t _Ebo = 0;
        glGenBuffers(1, &_Ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * _Indicies.size(), _Indicies.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * _StrideCount, (const void*)(0));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * _StrideCount, (const void*)(3 * sizeof(float)));
        glBindVertexArray(0);
    }
    m_FlatColorShader = std::make_unique<Shader>("res/shader/FlatColor.vert", "res/shader/FlatColor.frag");
}

void GameLayer::OnDetach() {

}

void GameLayer::OnUpdate(double _Dt) {
    double _GlobalTime = m_GlobalTimer.Time();
    float r = static_cast<float>(std::sin(_GlobalTime) + 1.0f) / 2;
    float g = static_cast<float>(std::sin(_GlobalTime * 1.5f) + 1.0f) / 2;
    float b = static_cast<float>(std::sin(_GlobalTime * 2.4f) + 1.0f) / 2;
    RendererAPI::ClearColor(r, g, b, 1.0f);
    RendererAPI::Clear();

    m_FlatColorShader->Bind();
    glBindVertexArray(m_SquareVA);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    m_FlatColorShader->UnBind();
}

void GameLayer::OnImGuiRender() {
    {
        ImGui::Begin("Game Debugger");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS).", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}

void GameLayer::OnEvent(Event& _Event) {

}


} // namespace Snake
