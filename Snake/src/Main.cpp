#include <Core/Application.h>
#include<iostream>
int main() {
    std::cout << "hello hao hao siao\n";
    auto& App = Application::GetInstance();
    App.Run();
    return 0;

}