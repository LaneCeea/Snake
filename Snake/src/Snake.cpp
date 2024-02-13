#include "Snake.h"

#include <Core/Log.h>
#include <Rng/Rng.h>

#include <algorithm>

namespace Snake {

Snake::Snake() :
    m_Body({
        glm::ivec2(0, 0),
        glm::ivec2(1, 0),
        glm::ivec2(2, 0),
        glm::ivec2(3, 0),
        glm::ivec2(4, 0)
    }),
    m_CurrentDir(MoveDirection::Right),
    m_Target({
        glm::ivec2(-3, -3),
        glm::ivec2(-5,  3),
        glm::ivec2( 4,  4),
    }),
    m_IsGameEnd(false) {

}

void Snake::Restart() {
    m_Body = {
        glm::ivec2(0, 0),
        glm::ivec2(1, 0),
        glm::ivec2(2, 0),
        glm::ivec2(3, 0),
        glm::ivec2(4, 0)
    };
    m_CurrentDir = MoveDirection::Right;
    m_Target = {
        glm::ivec2(-3, -3),
        glm::ivec2(-5,  3),
        glm::ivec2( 4,  4),
    };
    m_IsGameEnd = false;
}

void Snake::Move(MoveDirection _Dir){
    if (m_IsGameEnd)
        return;

    if (_Dir != MoveDirection::None && !IsMoveDirectionOpposite(_Dir, m_CurrentDir)) {
        m_CurrentDir = _Dir;
    }
    glm::ivec2 _NewHead = m_Body.back();
    switch (m_CurrentDir) {
    case Snake::MoveDirection::Up:
        _NewHead.y += 1;
        break;
    case Snake::MoveDirection::Down:
        _NewHead.y -= 1;
        break;
    case Snake::MoveDirection::Left:
        _NewHead.x -= 1;
        break;
    case Snake::MoveDirection::Right:
        _NewHead.x += 1;
        break;
    }

    auto _CollideBody = std::find(m_Body.begin(), m_Body.end(), _NewHead);
    if (_CollideBody != m_Body.end()) {
        m_IsGameEnd = true;
        return;
    }

    m_Body.push_back(_NewHead);

    auto _CollideTarget = std::find(m_Target.begin(), m_Target.end(), _NewHead);
    if (_CollideTarget != m_Target.end()) {
        m_Target.erase(_CollideTarget);

        auto& _Rand = RandomInt32<std::int32_t>::getInstance();
        _Rand.setParam(-15, 15);
        m_Target.emplace_back(_Rand.getNum(), _Rand.getNum());
    } else {
        m_Body.pop_front();
    }
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