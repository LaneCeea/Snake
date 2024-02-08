#include "Application.h"

#include <Core/Assert.h>
#include <Core/Timer.h>
#include <Renderer/RendererAPI.h>
#include <ImGui/ImGuiLayer.h>
#include <Event/Event.h>

#include <cmath>

Application* Application::s_Instance = nullptr;

Application::Application()
    : m_Window(), m_IsRunning(true), m_IsMinimized(false),
    m_ImGuiLayerPtr(), m_LayerStack() {
    
    CORE_ASSERT(s_Instance == nullptr, "Application already exist.");
    s_Instance = this;

    m_Window = std::make_unique<Window>("Snake");
    m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
    RendererAPI::Init();

    m_ImGuiLayerPtr = new ImGuiLayer();
    PushOverlay(m_ImGuiLayerPtr);
}

Application::~Application() {
    s_Instance = nullptr;
}

void Application::Run() {
    double _LastFrameTime = Timer::GlobalTime();
    while (m_IsRunning) {
        double _Time = Timer::GlobalTime();
        double _Dt = _Time - _LastFrameTime;
        _LastFrameTime = _Time;
        if (!m_IsMinimized) {
            

            for (Layer* const _LayerPtr : m_LayerStack) {
                _LayerPtr->OnUpdate(_Dt);
            }

            // imgui new frame
            m_ImGuiLayerPtr->Begin();

            for (Layer* const _LayerPtr : m_LayerStack) {
                _LayerPtr->OnImGuiRender();
            }

            m_ImGuiLayerPtr->End();
        }
        m_Window->OnUpdata();
    }
}

void Application::OnEvent(Event& _Event) {
    EventDispatcher _Dispatcher(_Event);

    _Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::_OnWindowClose));
    _Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(Application::_OnWindowResize));

    for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
        Layer* const _LayerPtr = *it;
        if (_Event.IsHandled())
            break;
        _LayerPtr->OnEvent(_Event);
    }
}

void Application::PushLayer(Layer* _LayerPtr){
    m_LayerStack.PushLayer(_LayerPtr);
    _LayerPtr->OnAttach();
}

void Application::PushOverlay(Layer* _OverlayPtr) {
    m_LayerStack.PushOverlay(_OverlayPtr);
    _OverlayPtr->OnAttach();
}

bool Application::_OnWindowClose(WindowCloseEvent& _Event) {
    m_IsRunning = false;
    return true;
}

bool Application::_OnWindowResize(WindowResizeEvent& _Event) {
	if (_Event.GetWidth() == 0 || _Event.GetHeight() == 0) {
		m_IsMinimized = true;
		return false;
	}

	m_IsMinimized = false;
	RendererAPI::SetViewPort(_Event.GetWidth(), _Event.GetHeight());

	return false;
}
