#include "GameLayer.h"

#include <Core/Input.h>
#include <ImGui/imgui.h>
#include <Renderer/RendererAPI.h>
#include <Renderer/VertexArray.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <array>
#include <cmath>

namespace Snake {

GameLayer::GameLayer() : 
    Layer("Snake::GameLayer"),
    m_Snake(), m_SquareVao(), m_FlatColorShader(), m_TickInterval(1.0 / 6.0), m_CurrentTimeBetweenTick(0.0) {
}

GameLayer::~GameLayer() {

}

void GameLayer::OnAttach() {
    m_GlobalTimer.Start();
    m_Igt.Start();
    {
        // Create m_SquareVA
        constexpr std::size_t _StrideCount = 7;
        const std::array<float, _StrideCount * 4> _Verticies = {
            // Positions       |  Colors                   |
            -0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, // 0
             0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, // 1
             0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, // 2
            -0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, // 3
        };

        const std::array<std::uint32_t, 6> _Indicies = {
            0, 1, 2, 2, 3, 0,
        };

        m_SquareVao = std::make_unique<VertexArray>(_Verticies, _Indicies,
            VertexLayout{
                ShaderDataType::Float3,
                ShaderDataType::Float4,
            });
    }
    m_FlatColorShader = std::make_unique<Shader>("res/shader/FlatColor.glsl");
}

void GameLayer::OnDetach() {
    m_SquareVao.release();
    m_FlatColorShader.release();
}

void GameLayer::OnUpdate(double _Dt) {

    m_CurrentTimeBetweenTick += _Dt;
    if (m_CurrentTimeBetweenTick >= m_TickInterval) {
        m_CurrentTimeBetweenTick -= m_TickInterval;
        if (Input::IsKeyPressed(Key::UP)) {
            m_Snake.Move(Snake::MoveDirection::Up);
        } else if (Input::IsKeyPressed(Key::DOWN)) {
            m_Snake.Move(Snake::MoveDirection::Down);
        } else if (Input::IsKeyPressed(Key::LEFT)) {
            m_Snake.Move(Snake::MoveDirection::Left);
        } else if (Input::IsKeyPressed(Key::RIGHT)) {
            m_Snake.Move(Snake::MoveDirection::Right);
        } else {
            m_Snake.Move(Snake::MoveDirection::None);
        }
    }

    double _GlobalTime = m_GlobalTimer.Time();
    float r = static_cast<float>(std::sin(_GlobalTime) + 1.0f) / 2;
    float g = static_cast<float>(std::sin(_GlobalTime * 1.5f) + 1.0f) / 2;
    float b = static_cast<float>(std::sin(_GlobalTime * 2.4f) + 1.0f) / 2;
    RendererAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    RendererAPI::Clear();

    const glm::mat4 _Proj       = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

    const glm::vec3 _Position   = glm::vec3(0.0f, 0.0f, -1.0f);
    const glm::vec3 _Front      = glm::vec3(0.0f, 0.0f,  1.0f);
    const glm::vec3 _Up         = glm::vec3(0.0f, 1.0f,  0.0f);
    const glm::mat4 _View       = glm::lookAt(_Position, _Position + _Front, _Up);

    const glm::mat4 _ProjView = _Proj * _View;

    m_FlatColorShader->Bind();

    const auto& _SnakeBody = m_Snake.Body();
    for (const auto& _Pos : _SnakeBody) {
        const glm::vec3 _Pos3D      = glm::vec3(_Pos, 0.0f);
        const glm::mat4 _Scale      = glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.01f));
        const glm::mat4 _Translate  = glm::translate(glm::identity<glm::mat4>(), _Pos3D);
        const glm::mat4 _Model      = _Scale * _Translate;
        m_FlatColorShader->SetUniform("u_Mvp", _ProjView * _Model);
        RendererAPI::Draw(*m_SquareVao);
    }

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
