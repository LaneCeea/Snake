#ifndef RENDERER_WINDOW_H_
#define RENDERER_WINDOW_H_

#include <Renderer/GraphicContext.h>

#include <string>

struct GLFWwindow;

class Window {
public:
    Window() = default;
    Window(const std::string& _title, std::uint32_t _width = 900, std::uint32_t _height = 900);
    ~Window();

    void OnUpdata();
    int ShouldClose();

    GLFWwindow* GetNativeWindow() { return m_Window; }
    std::uint32_t GetWidth() const { return m_Data.width; }
    std::uint32_t GetHeight() const { return m_Data.height; }
    bool IsVSync() const { return m_Data.VSync; }

    void SetVSync(bool enable);

    // need to remove
    static double GetTime();

private:
    GLFWwindow* m_Window;
    GraphicContext m_Context;

    struct WindowData {
        std::string title;
        std::uint32_t width, height;
        bool VSync;
    };

    WindowData m_Data;
};

#endif // !RENDERER_WINDOW_H_
