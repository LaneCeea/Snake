#ifndef CORE_LOG_H_
#define CORE_LOG_H_

#ifdef _DEBUG
#define CORE_ERROR(...)     Log(LogType::Error, __VA_ARGS__)
#define CORE_WARN(...)      Log(LogType::Warn,  __VA_ARGS__)
#define CORE_INFO(...)      Log(LogType::Info,  __VA_ARGS__)
#define CORE_TRACE(...)     Log(LogType::Trace, __VA_ARGS__)

#else // ^^^ _DEBUG ^^^ // vvv !_DEBUG vvv
#define CORE_ERROR(...)     (void)(__VA_ARGS__)
#define CORE_WARN(...)      (void)(__VA_ARGS__)
#define CORE_INFO(...)      (void)(__VA_ARGS__)
#define CORE_TRACE(...)     (void)(__VA_ARGS__)

#endif // _DEBUG

enum class LogType {
    None = 0, Error, Warn, Info, Trace
};

void Log(LogType type, const char* format, ...);

#endif // !CORE_LOG_H_