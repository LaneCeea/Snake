#include "Window.h"

#include <Core/Assert.h>
#include <Event/WindowEvent.h>
#include <Event/KeyEvent.h>

#include <GLFW/glfw3.h>

Window::Window(const std::string& _title, std::uint32_t _width, std::uint32_t _height) {
    int status = glfwInit();
    CORE_ASSERT(status, "Failed to initialize glfw.");
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // _DEBUG

    CORE_INFO("GLFW library binrary - %s\n\n", glfwGetVersionString());

    m_Window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
    CORE_ASSERT(m_Window, "Failed to create GLFWwindow.");

    m_Context = GraphicContext(m_Window);
    m_Context.Init();

    m_Data.title    = _title;
    m_Data.width    = _width;
    m_Data.height   = _height;
    SetVSync(false);

    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwSetWindowCloseCallback(m_Window,
        [](GLFWwindow* window) {
            WindowData* _Data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent _Event;
            _Data->EventCallBack(_Event);
        }
    );

    glfwSetWindowSizeCallback(m_Window,
        [](GLFWwindow* window, int width, int height) {
            WindowData* _Data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            _Data->width  = width;
            _Data->height = height;
            
            WindowResizeEvent _Event(width, height);
            _Data->EventCallBack(_Event);
        }
    );

    glfwSetKeyCallback(m_Window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData* _Data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            KeyEvent _Event(key, scancode, action, mods);
            _Data->EventCallBack(_Event);
        }
    );
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
    m_Context.Exit();
}

void Window::OnUpdata() {
    glfwPollEvents();
    m_Context.SwapBuffers();
}

int Window::ShouldClose() {
    return glfwWindowShouldClose(m_Window);
}

void Window::SetVSync(bool enable) {
    glfwSwapInterval(enable ? 1 : 0);
    m_Data.VSync = enable;
}
