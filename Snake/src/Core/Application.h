#ifndef CORE_APPLICATION_H_
#define CORE_APPLICATION_H_

#include <Core/LayerStack.h>
#include <Event/Event.h>
#include <Event/ApplicationEvent.h>
#include <ImGui/ImGuiLayer.h>
#include <Renderer/Window.h>

#include <memory>

class Application {
public:
    static Application& GetInstance() { return *s_Instance; }

protected:
    Application();

public:
    Application(const Application&)            = delete;
    Application& operator=(const Application&) = delete;
    ~Application();

    void Run();
    void OnEvent(Event& _Event);

    void PushLayer(Layer* _LayerPtr);
    void PushOverlay(Layer* _OverlayPtr);
    Window& GetWindow() { return *m_Window; }

public:
    bool _OnWindowClose(WindowCloseEvent& _Event);
    bool _OnWindowResize(WindowResizeEvent& _Event);

private:
    static Application* s_Instance;

    std::unique_ptr<Window> m_Window;
    bool m_IsRunning;
    bool m_IsMinimized;

    ImGuiLayer* m_ImGuiLayerPtr;
    LayerStack m_LayerStack;
};

// define in Application derived class
Application* CreateApplication();

#endif // !CORE_APPLICATION_H_
