#ifndef CORE_APPLICATION_H_
#define CORE_APPLICATION_H_

#include <Renderer/Window.h>

#include <memory>

class Application {
public:
    static Application& GetInstance();

private:
    Application();

public:
    Application(const Application&)            = delete;
    Application& operator=(const Application&) = delete;
    ~Application();

    void Run();

    Window& GetWindow() { return *m_Window; }

private:
    std::unique_ptr<Window> m_Window;
};


#endif // !CORE_APPLICATION_H_
