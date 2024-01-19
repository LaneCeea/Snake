#ifndef IMGUIAPI_IMGUIAPI_H_
#define IMGUIAPI_IMGUIAPI_H_

class ImGuiAPI {
public:
    static void Init();
    static void NewFrame();
    static void Render();
    static void Shutdown();
};

#endif // !IMGUIAPI_IMGUIAPI_H_
