#include "GraphicContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Core/Assert.h>

GraphicContext::GraphicContext(GLFWwindow* _WindowHandle)
    : m_WindowHandle(_WindowHandle){
    CORE_ASSERT(_WindowHandle, "Failed to create GraphicContext.");
}

void GraphicContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    CORE_ASSERT(status, "Failed to initialize glad.");
}

void GraphicContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}

void GraphicContext::Exit() {
    glfwTerminate();
}
