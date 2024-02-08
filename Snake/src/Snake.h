#ifndef SNAKE_SNAKE_H_
#define SNAKE_SNAKE_H_

#include <glm/ext/vector_int2.hpp>

#include <deque>

namespace Snake {

class Snake {
public:
    enum class MoveDirection {
        None = 0,
        Up, Down, Left, Right
    };

    using Container = std::deque<glm::ivec2>;

public:
    Snake();

    void Move(MoveDirection _Dir);

    const Container& Body() const { return m_Body; }

    void PrintBody() const;

    static bool IsMoveDirectionOpposite(MoveDirection _Lhs, MoveDirection _Rhs);

private:
    Container m_Body;
    MoveDirection m_CurrentDir;
};

} // namespace Snake

#endif // !SNAKE_SNAKE_H_
