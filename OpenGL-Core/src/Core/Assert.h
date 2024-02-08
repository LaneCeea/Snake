#ifndef CORE_ASSERT_H_
#define CORE_ASSERT_H_

#include <Core/Log.h>
#include <cstdlib>

#ifdef _DEBUG
#define CORE_ASSERT(expression, message)                                                        \
    if (!(expression)) {                                                                      \
        CORE_ERROR("Assertion failed at %s(%d): %s\n", __FILE__, __LINE__ , message);   \
        std::abort();                                                                       \
    }

#else // ^^^ _DEBUG ^^^ // vvv !_DEBUG vvv
#define CORE_ASSERT(expression, message) (void)(expression, message)

#endif // _DEBUG

#endif // !CORE_ASSERT_H_