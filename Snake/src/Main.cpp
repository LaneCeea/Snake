#include <Core/Application.h>

#include <iostream>

int main() {
    std::cout << "hello hao hao siao\n";

    auto App = CreateApplication();
    App->Run();
    delete App;

    return 0;
}