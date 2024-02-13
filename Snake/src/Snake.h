#ifndef SNAKE_SNAKE_H_
#define SNAKE_SNAKE_H_

#include <glm/ext/vector_int2.hpp>

#include <deque>
#include <vector>

namespace Snake {

class Snake {
public:
    enum class MoveDirection {
        None = 0,
        Up, Down, Left, Right
    };

    using Coord             = glm::ivec2;
    using BodyContainer     = std::deque<glm::ivec2>;
    using TargetContainer   = std::vector<glm::ivec2>;

public:
    Snake();

    void Restart();
    void Move(MoveDirection _Dir);

    const BodyContainer& Body() const       { return m_Body; }
    const TargetContainer& Target() const   { return m_Target; }
    constexpr bool IsGameEnd() const        { return m_IsGameEnd; }

    void PrintBody() const;

    static bool IsMoveDirectionOpposite(MoveDirection _Lhs, MoveDirection _Rhs);

private:
    BodyContainer m_Body;
    MoveDirection m_CurrentDir;
    TargetContainer m_Target;

    bool m_IsGameEnd;
};

} // namespace Snake

#endif // !SNAKE_SNAKE_H_
