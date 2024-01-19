#ifndef IMGUI_IMGUIAPI_H_
#define IMGUI_IMGUIAPI_H_

class ImGuiAPI {
public:
    static void Init();
    static void NewFrame();
    static void Render();
    static void Shutdown();
};

#endif // !IMGUI_IMGUIAPI_H_
