#include "RendererAPI.h"

#include <Core/Log.h>

#include <glad/glad.h>

#ifdef _DEBUG

static void APIENTRY _ErrorCallBack(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam) {

    if (id == 131185) return;

    const char* source_str;
    switch (source) {
    case GL_DEBUG_SOURCE_API:               source_str = "API";                 break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     source_str = "Window System";       break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:   source_str = "Shader Compiler";     break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:       source_str = "Third Party";         break;
    case GL_DEBUG_SOURCE_APPLICATION:       source_str = "Application";         break;
    case GL_DEBUG_SOURCE_OTHER:             source_str = "Other";               break;
    default:                                source_str = "";                    break;
    }

    const char* type_str;
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:               type_str = "Error";                 break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "Deprecated Behaviour";  break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_str = "Undefined Behaviour";   break; 
    case GL_DEBUG_TYPE_PORTABILITY:         type_str = "Portability";           break;
    case GL_DEBUG_TYPE_PERFORMANCE:         type_str = "Performance";           break;
    case GL_DEBUG_TYPE_MARKER:              type_str = "Marker";                break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          type_str = "Push Group";            break;
    case GL_DEBUG_TYPE_POP_GROUP:           type_str = "Pop Group";             break;
    case GL_DEBUG_TYPE_OTHER:               type_str = "Other";                 break;
    default:                                type_str = "";                      break;
    }
    
    LogType logtype = LogType::NONE;
    const char* severity_str;
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:            severity_str = "high";          logtype = LogType::ERR;     break;
    case GL_DEBUG_SEVERITY_MEDIUM:          severity_str = "medium";        logtype = LogType::ERR;     break;
    case GL_DEBUG_SEVERITY_LOW:             severity_str = "low";           logtype = LogType::WARN;    break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:    severity_str = "notification";  logtype = LogType::INFO;    break;
    default:                                severity_str = "";              logtype = LogType::NONE;    break;
    }

    Log(logtype,
        "[OpenGL Log](%u)\n"
        "Source: %s\n"
        "Type: %s\n"
        "Severity: %s\n"
        "- %s\n\n",
        id, source_str, type_str, severity_str, message);
}

#endif // _DEBUG

void RendererAPI::Init() {
#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(_ErrorCallBack, nullptr);
#endif // _DEBUG

    const unsigned char* version    = glGetString(GL_VERSION);
    const unsigned char* vendor     = glGetString(GL_VENDOR);
    const unsigned char* renderer   = glGetString(GL_RENDERER);
    CORE_INFO(
        "OpenGL   - %s\n"
        "Vendor   - %s\n"
        "Renderer - %s\n\n",
        version, vendor, renderer
    );

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void RendererAPI::ClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void RendererAPI::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
