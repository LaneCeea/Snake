#ifndef CORE_INPUT_H_
#define CORE_INPUT_H_

#include <Core/KeyCode.h>

class Input {
public:
    static bool IsKeyPressed(Key::KeyCode _Key);
};

#endif // !CORE_INPUT_H_
