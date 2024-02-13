#include "Shader.h"

#include <Core/Log.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>

Shader::Shader() :
    m_ReferenceID(0), m_IsBind(false), m_UniformLocationMap() {
}

Shader::Shader(std::string_view _glslPath) {
    Init(_glslPath);
}

Shader::~Shader() {
    if (m_ReferenceID)
        Destroy();
}

void Shader::Init(std::string_view _glslPath) {
    m_ReferenceID = glCreateProgram();
    m_IsBind = false;

    std::uint32_t _VertShader = glCreateShader(GL_VERTEX_SHADER);
    std::uint32_t _FragShader = glCreateShader(GL_FRAGMENT_SHADER);

    const std::string _VertExt(".vert");
    const std::string _FragExt(".frag");
    const std::string _glslPathStr(_glslPath);
    _CompileShader(_VertShader, _glslPathStr + _VertExt);
    _CompileShader(_FragShader, _glslPathStr + _FragExt);

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

void Shader::Destroy() {
    glDeleteProgram(m_ReferenceID);
    m_ReferenceID = 0;
    m_IsBind = false;
    m_UniformLocationMap.clear();
}

void Shader::Bind() const {
    if (m_IsBind) {
        CORE_WARN("Attempt to bind an already bind shader.\n");
        return;
    }
    m_IsBind = true;
    glUseProgram(m_ReferenceID);
}

void Shader::UnBind() const {
    if (!m_IsBind) {
        CORE_WARN("Attempt to unbind an already unbind shader.\n");
        return;
    }
    m_IsBind = false;
    glUseProgram(0);
}

void Shader::_CompileShader(std::uint32_t& _ShaderID, const std::string& _FilePath) {
    const std::string _VertString = _ReadFile(_FilePath);
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
        CORE_TRACE("Shader compile success: %s\n", _FilePath.data());
    }
}

std::string Shader::_ReadFile(const std::string& _FilePath) {
    constexpr std::size_t _ReadSize = 1024;
    std::string _Out;
    std::string _Buffer(_ReadSize, '\0');

    std::ifstream _Stream(_FilePath.data());
    if (_Stream.fail()) {
        CORE_ERROR("File '%s' does not exist.\n", _FilePath.data());
        return _Out;
    }

    while (_Stream.read(_Buffer.data(), _ReadSize)) {
        _Out.append(_Buffer, 0, _Stream.gcount());
    }
    _Out.append(_Buffer, 0, _Stream.gcount());

    return _Out;
}

void Shader::SetUniform(const std::string_view& _UniformName, float v0) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform1f(location, v0);
}

void Shader::SetUniform(const std::string_view& _UniformName, float v0, float v1) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform2f(location, v0, v1);
}

void Shader::SetUniform(const std::string_view& _UniformName, float v0, float v1, float v2) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform3f(location, v0, v1, v2);
}

void Shader::SetUniform(const std::string_view& _UniformName, float v0, float v1, float v2, float v3) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform4f(location, v0, v1, v2, v3);
}

void Shader::SetUniform(const std::string_view& _UniformName, const glm::vec2& vec) const {
    SetUniform(_UniformName, vec.x, vec.y);
}

void Shader::SetUniform(const std::string_view& _UniformName, const glm::vec3& vec) const {
    SetUniform(_UniformName, vec.x, vec.y, vec.z);
}

void Shader::SetUniform(const std::string_view& _UniformName, const glm::vec4& vec) const {
    SetUniform(_UniformName, vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniform(const std::string_view& _UniformName, int v0) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform1i(location, v0);
}

void Shader::SetUniform(const std::string_view& _UniformName, int v0, int v1) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform2i(location, v0, v1);
}

void Shader::SetUniform(const std::string_view& _UniformName, int v0, int v1, int v2) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform3i(location, v0, v1, v2);
}

void Shader::SetUniform(const std::string_view& _UniformName, int v0, int v1, int v2, int v3) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform4i(location, v0, v1, v2, v3);
}

void Shader::SetUniform(const std::string_view& _UniformName, std::uint32_t v0) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform1ui(location, v0);
}

void Shader::SetUniform(const std::string_view& _UniformName, std::uint32_t v0, std::uint32_t v1) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform2ui(location, v0, v1);
}

void Shader::SetUniform(const std::string_view& _UniformName, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform3ui(location, v0, v1, v2);
}

void Shader::SetUniform(const std::string_view& _UniformName, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniform4ui(location, v0, v1, v2, v3);
}

void Shader::SetUniform(const std::string_view& _UniformName, const glm::mat3& mat) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetUniform(const std::string_view& _UniformName, const glm::mat4& mat) const {
    int location = _GetUniformLocation(_UniformName.data());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

std::int32_t Shader::_GetUniformLocation(std::string_view _UniformName) const {
    auto _It = m_UniformLocationMap.find(_UniformName);
    if (_It != m_UniformLocationMap.end())
        return _It->second;

    int _Location = glGetUniformLocation(m_ReferenceID, _UniformName.data());
    if (_Location == -1)
        CORE_WARN("Uniform '%s' does not exist.\n", _UniformName.data());

    m_UniformLocationMap.emplace(_UniformName, _Location);
    return _Location;
}
