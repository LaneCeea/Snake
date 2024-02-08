#ifndef SNAKE_GAMEAPP_H_
#define SNAKE_GAMEAPP_H_

#include "GameLayer.h"

#include <Core/Application.h>

namespace Snake {

class GameApp : public Application {
public:
    GameApp() {
        PushLayer(new GameLayer);
    }
};

} // namespace Snake

#endif // !SNAKE_GAMEAPP_H_
