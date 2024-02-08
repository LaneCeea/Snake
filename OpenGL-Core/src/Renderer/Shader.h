#ifndef RENDERER_SHADER_H_
#define RENDERER_SHADER_H_

#include <cstdint>
#include <string_view>

class Shader {
public:
    Shader(std::string_view _VertPath, std::string_view _FragPath);

    void Bind();
    void UnBind();

private:
    static std::string _ReadFile(std::string_view _FilePath);
    static void _CompileShader(std::uint32_t& _ShaderID, std::string_view _FilePath);

private:
    std::uint32_t m_ReferenceID;
    bool m_IsBind;
};

#endif // !RENDERER_SHADER_H_
