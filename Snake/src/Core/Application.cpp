#include "Application.h"

#include <Renderer/RendererAPI.h>
#include <ImGuiAPI/ImGuiAPI.h>

#include <cmath>

Application& Application::GetInstance() {
    static Application s_Instance;
    return s_Instance;
}

Application::Application()
    : m_Window(std::make_unique<Window>("Snake")) {
    RendererAPI::Init();
}

Application::~Application() {
    ImGuiAPI::Shutdown();
    m_Window.release();
}

void Application::Run() {
    ImGuiAPI::Init();
    float Time = 0;
    while (!m_Window->ShouldClose()) {
        Time = static_cast<float>(Window::GetTime());
        float r = (std::sin(Time) + 1.0f) / 2;
        float g = (std::sin(Time * 1.5f) + 1.0f) / 2;
        float b = (std::sin(Time * 2.4f) + 1.0f) / 2;

        // imgui new frame
        ImGuiAPI::NewFrame();

        RendererAPI::ClearColor(r, g, b, 1.0f);
        RendererAPI::Clear();

        ImGuiAPI::Render();

        m_Window->OnUpdata();
    }
}
