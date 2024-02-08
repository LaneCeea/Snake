#include "Shader.h"

#include <Core/Log.h>

#include <glad/glad.h>

#include <fstream>

Shader::Shader(std::string_view _VertPath, std::string_view _FragPath) {
    m_ReferenceID = glCreateProgram();
    m_IsBind = false;

    std::uint32_t _VertShader = glCreateShader(GL_VERTEX_SHADER);
    std::uint32_t _FragShader = glCreateShader(GL_FRAGMENT_SHADER);
    _CompileShader(_VertShader, _VertPath);
    _CompileShader(_FragShader, _FragPath);

    glAttachShader(m_ReferenceID, _VertShader);
    glAttachShader(m_ReferenceID, _FragShader);
    glLinkProgram(m_ReferenceID);

    glDeleteShader(_VertShader);
    glDeleteShader(_FragShader);

    std::int32_t _Success = 0;
    glGetProgramiv(m_ReferenceID, GL_LINK_STATUS, &_Success);
    if (!_Success) {
        std::int32_t _Length = 0;
        glGetShaderiv(m_ReferenceID, GL_INFO_LOG_LENGTH, &_Length);

        std::string _Message(_Length, '\0');
        glGetShaderInfoLog(m_ReferenceID, _Length, nullptr, _Message.data());

        CORE_ERROR("Failed to link shader program - %s\n", _Message.c_str());
    }
}

void Shader::Bind() {
    if (m_IsBind) {
        CORE_WARN("Attempt to bind an already bind shader.\n");
        return;
    }
    m_IsBind = true;
    glUseProgram(m_ReferenceID);
}

void Shader::UnBind() {
    if (!m_IsBind) {
        CORE_WARN("Attempt to unbind an already unbind shader.\n");
        return;
    }
    m_IsBind = false;
    glUseProgram(0);
}

std::string Shader::_ReadFile(std::string_view _FilePath) {
    constexpr std::size_t _ReadSize = 1024;
    std::string _Out;
    std::string _Buffer(_ReadSize, '\0');

    std::ifstream _Stream(_FilePath.data());
    if (_Stream.fail()) {
        CORE_ERROR("File does not exist: %s.\n", _FilePath.data());
        return _Out;
    }

    while (_Stream.read(_Buffer.data(), _ReadSize)) {
        _Out.append(_Buffer, 0, _Stream.gcount());
    }
    _Out.append(_Buffer, 0, _Stream.gcount());

    return _Out;
}

void Shader::_CompileShader(std::uint32_t& _ShaderID, std::string_view _FilePath) {
    std::string _VertString = _ReadFile(_FilePath);
    const char* _VertSource = _VertString.c_str();

    glShaderSource(_ShaderID, 1, &_VertSource, nullptr);
    glCompileShader(_ShaderID);

    std::int32_t _Success = 0;
    glGetShaderiv(_ShaderID, GL_COMPILE_STATUS, &_Success);
    if (!_Success) {
        std::int32_t _Length = 0;
        glGetShaderiv(_ShaderID, GL_INFO_LOG_LENGTH, &_Length);

        std::string _Message(_Length, '\0');
        glGetShaderInfoLog(_ShaderID, _Length, nullptr, _Message.data());

        CORE_ERROR("Failed to compile shader - %s\n", _Message.c_str());
        glDeleteShader(_ShaderID);
    } else {
        CORE_TRACE("Shader compile success : %s\n", _FilePath.data());
    }
}
