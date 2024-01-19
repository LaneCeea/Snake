#include "Log.h"

#include <cstdarg>
#include <cstdio>

#include <Windows.h>

void Log(LogType type, const char* format, ...) {
    static constexpr WORD red    = FOREGROUND_RED;
    static constexpr WORD yellow = FOREGROUND_RED | FOREGROUND_GREEN;
    static constexpr WORD white  = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    static HANDLE s_Console      = GetStdHandle(STD_OUTPUT_HANDLE);

    WORD text_color = 0;
    switch (type) {
    case LogType::ERR:  text_color = red;       break;
    case LogType::WARN: text_color = yellow;    break;
    case LogType::INFO: text_color = white;     break;
    }
    SetConsoleTextAttribute(s_Console, text_color);

    std::va_list args;
    va_start(args, format);
    std::vprintf(format, args);
    va_end(args);
    SetConsoleTextAttribute(s_Console, white);
}