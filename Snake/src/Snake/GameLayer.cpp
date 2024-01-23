#include "GameLayer.h"

#include <ImGui/imgui.h>
#include <Renderer/RendererAPI.h>

#include <cmath>

namespace Snake {

GameLayer::GameLayer()
    : Layer("Snake::GameLayer") {
    m_GlobalTimer.Start();
}

GameLayer::~GameLayer() {

}

void GameLayer::OnAttach() {

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
