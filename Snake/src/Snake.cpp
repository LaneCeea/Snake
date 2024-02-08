#include "Snake.h"

#include <Core/Log.h>

namespace Snake {

Snake::Snake() :
    m_Body({
        glm::ivec2(0, 0),
        glm::ivec2(1, 0),
        glm::ivec2(2, 0),
        glm::ivec2(3, 0),
        glm::ivec2(4, 0)
    }),
    m_CurrentDir(MoveDirection::Right) {

}

void Snake::Move(MoveDirection _Dir){
    if (_Dir != MoveDirection::None && !IsMoveDirectionOpposite(_Dir, m_CurrentDir)) {
        m_CurrentDir = _Dir;
    }
    m_Body.pop_front();
    glm::ivec2 _NewHead = m_Body.back();;
    switch (m_CurrentDir) {
    case Snake::MoveDirection::Up:
        _NewHead.y += 1;
        break;
    case Snake::MoveDirection::Down:
        _NewHead.y -= 1;
        break;
    case Snake::MoveDirection::Left:
        _NewHead.x += 1;
        break;
    case Snake::MoveDirection::Right:
        _NewHead.x -= 1;
        break;
    }
    m_Body.push_back(_NewHead);
}

void Snake::PrintBody() const {
    CORE_TRACE("Snake.m_Body");
    for (const auto& _Pos : m_Body) {
        CORE_TRACE("(%d, %d), ", _Pos.x, _Pos.y);
    }
    CORE_TRACE("\n");
}

bool Snake::IsMoveDirectionOpposite(MoveDirection _Lhs, MoveDirection _Rhs) {
    return (
        (_Lhs == MoveDirection::Up    && _Rhs == MoveDirection::Down)   ||
        (_Lhs == MoveDirection::Down  && _Rhs == MoveDirection::Up)     ||
        (_Lhs == MoveDirection::Left  && _Rhs == MoveDirection::Right)  ||
        (_Lhs == MoveDirection::Right && _Rhs == MoveDirection::Left)
    );
}

} // namespace Snake