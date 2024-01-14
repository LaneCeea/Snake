#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <cstdio>
#include <cmath>

int main() {
    // glfw init
    if (!glfwInit()) {
        std::printf("[Error] Failed to initialize glfw.\n");
        return -1;
    }
    
    // create window
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

    // glad init
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

    // imgui init
    if (!IMGUI_CHECKVERSION()) {
        std::printf("[Error] Failed to initialize Dear ImGui.\n");
        return -1;
    }
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    if (!ImGui_ImplGlfw_InitForOpenGL(Window, true)) {
        std::printf("[Error] Failed to initialize imgui_impl_glfw backend.\n");
        return -1;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 460")) {
        std::printf("[Error] Failed to initialize imgui_impl_opengl3 backend.\n");
        return -1;
    }
    std::printf("Dear ImGui version - %s\n\n", IMGUI_VERSION);

    float Time = 0;

    while (!glfwWindowShouldClose(Window)) {
        Time = static_cast<float>(glfwGetTime());
        float r = (std::sin(Time) + 1.0f) / 2;
        float g = (std::sin(Time * 1.5f) + 1.0f) / 2;
        float b = (std::sin(Time * 2.4f) + 1.0f) / 2;

        // imgui new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // imgui render
        {
            ImGui::Begin("Dear ImGui Debugger");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS).", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // window swap buffer
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
    
    // imgui exit
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(Window);
    glfwTerminate();

    return 0;
}