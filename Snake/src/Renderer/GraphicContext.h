#ifndef RENDERER_GRAPHICCONTEXT_H_
#define RENDERER_GRAPHICCONTEXT_H_

struct GLFWwindow;

class GraphicContext {
public:
    GraphicContext() = default;
    GraphicContext(GLFWwindow* _WindowHandle);
    void Init();
    void SwapBuffers();
    void Exit();

private:
    GLFWwindow* m_WindowHandle;
};

#endif // !RENDERER_GRAPHICCONTEXT_H_
