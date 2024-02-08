#include "Input.h"

#include <Core/Application.h>

#include <GLFW/glfw3.h>

bool Input::IsKeyPressed(KeyCode _Key) {
    auto* _Window = Application::GetInstance().GetWindow().GetNativeWindow();
    auto _State = glfwGetKey(_Window, static_cast<int32_t>(_Key));
    return _State == GLFW_PRESS;
}
