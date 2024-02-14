#include "GameLayer.h"

#include <Core/Input.h>
#include <Core/Application.h> // for proj matrix
#include <ImGui/imgui.h>
#include <Renderer/Renderer.h>
#include <Renderer/RendererAPI.h>
#include <Renderer/VertexArray.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <array>
#include <cmath>

namespace Snake {

GameLayer::GameLayer() : 
    Layer("Snake::GameLayer"),
    m_Snake(), m_SnakeNextDir(Snake::MoveDirection::None),
    m_FlatColorShader(), m_BasicTextureShader(), m_ExplosionTexture(),
    m_TickInterval(1.0 / 10.0), m_CurrentTimeBetweenTick(0.0),
    m_IsRunning(false) {
}

GameLayer::~GameLayer() {

}

void GameLayer::OnAttach() {
    m_GlobalTimer.Start();
    m_Igt.Start();
    m_Igt.Pause();
    m_FlatColorShader.Init("res/shader/FlatColor.glsl");
    m_BasicTextureShader.Init("res/shader/BasicTexture.glsl");
    m_ExplosionTexture.Init("res/texture/Explosion.png");
}

void GameLayer::OnDetach() {
    m_FlatColorShader.Destroy();
    m_BasicTextureShader.Destroy();
    m_ExplosionTexture.Destroy();
}

void GameLayer::OnUpdate(double _Dt) {

    if (m_IsRunning && !m_Snake.IsGameEnd()) {
        double _LastTime = m_Igt.Last();
        double _CurrTime = m_Igt.Now();

        m_CurrentTimeBetweenTick += _CurrTime - _LastTime;
        if (m_CurrentTimeBetweenTick >= m_TickInterval) {
            m_CurrentTimeBetweenTick -= m_TickInterval;

            // key press is query by key event to detect pressing between frame
            m_Snake.Move(m_SnakeNextDir);
        }
    }

    RendererAPI::Clear();

    auto _WindowDimension       = Application::GetInstance().GetWindow().GetDimension();
    float _Ratio                = static_cast<float>(_WindowDimension.x) / _WindowDimension.y;
    const glm::mat4 _Proj       = glm::perspective(glm::radians(45.0f), _Ratio, 0.1f, 100.0f);

    const glm::vec3 _Position   = glm::vec3(0.0f, 0.0f, 20.0f);
    const glm::vec3 _Front      = glm::vec3(0.0f, 0.0f, -1.0f);
    const glm::vec3 _Up         = glm::vec3(0.0f, 1.0f,  0.0f);
    const glm::mat4 _View       = glm::lookAt(_Position, _Position + _Front, _Up);

    const glm::mat4 _ProjView = _Proj * _View;

    m_FlatColorShader.Bind();
    const auto& _SnakeBody = m_Snake.Body();
    const auto& _SnakeHead = m_Snake.Head();
    for (const auto& _Pos : _SnakeBody) {
        const glm::vec3 _Pos3D      = glm::vec3(_Pos, 0.0f);
        const glm::mat4 _Scale      = glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.0f));
        const glm::mat4 _Translate  = glm::translate(glm::identity<glm::mat4>(), _Pos3D);
        const glm::mat4 _Model      = _Translate * _Scale;
        const glm::vec4 _Color      = 
            _Pos == _SnakeHead ?
            glm::vec4(0.5f, 0.5f, 0.5f, 1.0f) :
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        m_FlatColorShader.SetUniform("u_Mvp", _ProjView * _Model);
        m_FlatColorShader.SetUniform("u_Color", _Color);
        Renderer::DrawSquare();
    }
    m_FlatColorShader.UnBind();

    m_FlatColorShader.Bind();

    const auto& _SnakeTarget = m_Snake.Target();
    for (const auto& _Pos : _SnakeTarget) {
        const glm::vec3 _Pos3D      = glm::vec3(_Pos, 0.0f);
        const glm::mat4 _Scale      = glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.0f));
        const glm::mat4 _Translate  = glm::translate(glm::identity<glm::mat4>(), _Pos3D);
        const glm::mat4 _Model      = _Translate * _Scale;
        m_FlatColorShader.SetUniform("u_Mvp", _ProjView * _Model);
        m_FlatColorShader.SetUniform("u_Color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        Renderer::DrawSquare();
    }

    m_FlatColorShader.UnBind();
    
    if (m_Snake.IsGameEnd()) {
        m_BasicTextureShader.Bind();
        m_ExplosionTexture.Bind(0);
        m_BasicTextureShader.SetUniform("u_Texture", (std::int32_t)0);
        
        const auto& _HeadPos        = m_Snake.Head();
        const glm::vec3 _Pos3D      = glm::vec3(_HeadPos, 0.5f);
        const glm::mat4 _Scale      = glm::scale(glm::identity<glm::mat4>(), glm::vec3(5.0f));
        const glm::mat4 _Translate  = glm::translate(glm::identity<glm::mat4>(), _Pos3D);
        const glm::mat4 _Model      = _Translate * _Scale;
        m_BasicTextureShader.SetUniform("u_Mvp", _ProjView * _Model);
        m_BasicTextureShader.SetUniform("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        Renderer::DrawSquare();
        
        m_ExplosionTexture.UnBind();
        m_BasicTextureShader.UnBind();
    }
}

void GameLayer::OnImGuiRender() {
    {
        ImGui::Begin("Game Debugger");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS).", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Press ESC to start/pause/resume.");
        ImGui::Text("IGT: %.3f", m_Igt.Last());
        if (m_Snake.IsGameEnd()) {
            ImGui::Text("Game has ended, press ENTER to start a new game.");
        }
        ImGui::End();
    }
}

void GameLayer::OnEvent(Event& _Event) {
    EventDispatcher _Dispatcher(_Event);

    _Dispatcher.Dispatch<KeyEvent>(BIND_EVENT_FUNC(OnKeyEvent));
}

bool GameLayer::OnKeyEvent(KeyEvent& _KeyEvent) {
    if (_KeyEvent.Action() == Key::Action::PRESS) {

        switch (_KeyEvent.Key()) {
        case Key::ESCAPE: {
            m_IsRunning = !m_IsRunning;
            if (m_IsRunning) {
                m_Igt.Resume();
            } else {
                m_Igt.Pause();
            }
            return true;
        }
        case Key::KP_ENTER:
        case Key::ENTER: {
            if (m_Snake.IsGameEnd()) {
                m_Snake.Restart();
                m_Igt.Reset();
                m_Igt.Start();
                return true;
            }
            break;
        }
        case Key::UP: {
            m_SnakeNextDir = Snake::MoveDirection::Up;
            return true;
        }
        case Key::DOWN: {
            m_SnakeNextDir = Snake::MoveDirection::Down;
            return true;
        }
        case Key::LEFT: {
            m_SnakeNextDir = Snake::MoveDirection::Left;
            return true;
        }
        case Key::RIGHT: {
            m_SnakeNextDir = Snake::MoveDirection::Right;
            return true;
        }
        default:
            break;
        }
    }
    return false;
}


} // namespace Snake
