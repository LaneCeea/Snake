#include <Core/Application.h>

int main() {
    auto& App = Application::GetInstance();
    App.Run();
    return 0;
}