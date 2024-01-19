#ifndef CORE_ASSERT_H_
#define CORE_ASSERT_H_

#include <Core/Log.h>
#include <cstdlib>

#ifdef _DEBUG
#define CORE_ASSERT(expression, ...)                                                        \
    if (!expression) {                                                                      \
        CORE_ERROR("Assertion failed at %s(%d): %s\n", __FILE__, __LINE__ , __VA_ARGS__);   \
        std::abort();                                                                       \
    }

#else // ^^^ _DEBUG ^^^ // vvv !_DEBUG vvv
#define CORE_ASSERT(expression, type, ...) (void)(expression, type, __VA_ARGS__)

#endif // _DEBUG

#endif // !CORE_ASSERT_H_