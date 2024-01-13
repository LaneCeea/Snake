#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cmath>

int main() {
    if (!glfwInit()) {
        std::printf("[Error] Failed to initialize glfw.\n");
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    std::printf("GLFW library binrary - %s\n\n", glfwGetVersionString());

    GLFWwindow* Window = glfwCreateWindow(900, 900, "Snake", nullptr, nullptr);
    if (!Window) {
        std::printf("[Error] Failed to create GLFWwindow.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::printf("[Error] Failed to initialize glad!\n");
        return -1;
    }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    const unsigned char* version    = glGetString(GL_VERSION);
    const unsigned char* vendor     = glGetString(GL_VENDOR);
    const unsigned char* renderer   = glGetString(GL_RENDERER);
    std::printf(
        "OpenGL   - %s\n"
        "Vendor   - %s\n"
        "Renderer - %s\n\n",
        version, vendor, renderer
    );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    float Time = 0;

    while (!glfwWindowShouldClose(Window)) {
        Time = static_cast<float>(glfwGetTime());
        float r = (std::sin(Time) + 1.0f) / 2;
        float g = (std::sin(Time * 1.5f) + 1.0f) / 2;
        float b = (std::sin(Time * 2.4f) + 1.0f) / 2;
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    glfwDestroyWindow(Window);
    glfwTerminate();

    return 0;
}