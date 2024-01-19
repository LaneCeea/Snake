#include "ImGuiAPI.h"

#include <Core/Application.h>
#include <Core/Assert.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

void ImGuiAPI::Init() {
    // imgui init
    bool success = IMGUI_CHECKVERSION();
    CORE_ASSERT(success, "Failed to initialize Dear ImGui.");

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    success = ImGui_ImplGlfw_InitForOpenGL(Application::GetInstance().GetWindow().GetNativeWindow(), true);
    CORE_ASSERT(success, "Failed to initialize imgui_impl_glfw backend.");

    success = ImGui_ImplOpenGL3_Init("#version 460");
    CORE_ASSERT(success, "Failed to initialize imgui_impl_opengl3 backend.");

    CORE_INFO("Dear ImGui version - %s\n\n", IMGUI_VERSION);
}

void ImGuiAPI::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiAPI::Render() {
    {
        ImGui::Begin("Dear ImGui Debugger");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS).", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiAPI::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
