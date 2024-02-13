#ifndef RENDERER_WINDOW_H_
#define RENDERER_WINDOW_H_

#include <Renderer/GraphicContext.h>
#include <Event/Event.h>

#include <glm/ext/vector_uint2.hpp>

#include <string>
#include <functional>

struct GLFWwindow;

class Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    Window() = default;
    Window(const std::string& _title, std::uint32_t _width = 900, std::uint32_t _height = 900);
    ~Window();

    void OnUpdata();
    int ShouldClose();

    GLFWwindow* GetNativeWindow() { return m_Window; }
    std::uint32_t GetWidth() const { return m_Data.width; }
    std::uint32_t GetHeight() const { return m_Data.height; }
    glm::uvec2 GetDimension() const { return { m_Data.width, m_Data.height }; }
    bool IsVSync() const { return m_Data.VSync; }

    void SetEventCallback(const EventCallbackFn& _Func) { m_Data.EventCallBack = _Func; }
    void SetVSync(bool enable);

private:
    GLFWwindow* m_Window;
    GraphicContext m_Context;

    struct WindowData {
        std::string title;
        std::uint32_t width, height;
        bool VSync;
        EventCallbackFn EventCallBack;
    };

    WindowData m_Data;
};

#endif // !RENDERER_WINDOW_H_
