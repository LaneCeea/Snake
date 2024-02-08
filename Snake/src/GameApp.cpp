#include "GameApp.h"

#include <Core/Application.h>

Application* CreateApplication() {
    return new Snake::GameApp();
}