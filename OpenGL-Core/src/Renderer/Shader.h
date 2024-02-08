#ifndef RENDERER_SHADER_H_
#define RENDERER_SHADER_H_

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/matrix_float3x3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include <string>
#include <string_view>
#include <unordered_map>
#include <cstdint>

class Shader {
public:
    Shader(std::string_view _glslPath);

    void Bind();
    void UnBind();

private:
    static void _CompileShader(std::uint32_t& _ShaderID, const std::string& _FilePath);
    static std::string _ReadFile(const std::string& _FilePath);

public:
    void SetUniform(const std::string_view& name, float v0) const;
    void SetUniform(const std::string_view& name, float v0, float v1) const;
    void SetUniform(const std::string_view& name, float v0, float v1, float v2) const;
    void SetUniform(const std::string_view& name, float v0, float v1, float v2, float v3) const;
    void SetUniform(const std::string_view& name, const glm::vec2& vec) const;
    void SetUniform(const std::string_view& name, const glm::vec3& vec) const;
    void SetUniform(const std::string_view& name, const glm::vec4& vec) const;
    void SetUniform(const std::string_view& name, int v0) const;
    void SetUniform(const std::string_view& name, int v0, int v1) const;
    void SetUniform(const std::string_view& name, int v0, int v1, int v2) const;
    void SetUniform(const std::string_view& name, int v0, int v1, int v2, int v3) const;
    void SetUniform(const std::string_view& name, std::uint32_t v0) const;
    void SetUniform(const std::string_view& name, std::uint32_t v0, std::uint32_t v1) const;
    void SetUniform(const std::string_view& name, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2) const;
    void SetUniform(const std::string_view& name, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3) const;
    void SetUniform(const std::string_view& name, const glm::mat3& mat) const;
    void SetUniform(const std::string_view& name, const glm::mat4& mat) const;

private:
    std::int32_t _GetUniformLocation(std::string_view _UniformName) const;

private:
    std::uint32_t m_ReferenceID;
    bool m_IsBind;
    mutable std::unordered_map<std::string_view, std::int32_t> m_UniformLocationMap;
};

#endif // !RENDERER_SHADER_H_
