#include <Core/Application.h>

#include <iostream>

int main() {
    std::cout << "hello hao hao siao\n";
    std::cout << "no hello hao hao siao\n";
    Application* App = CreateApplication();
    App->Run();
    delete App;

    return 0;
}