#ifndef RENFERER_TEXTURE_H_
#define RENFERER_TEXTURE_H_

#include <glm/ext/vector_int2.hpp>

#include <string_view>
#include <cstdint>

class Texture {
public:
    Texture() = default;
    Texture(std::string_view _ImagePath);
    ~Texture();

    void Init(std::string_view _ImagePath);
    void Destroy();

    void Bind(std::uint32_t _TextureUnit) const;
    void UnBind() const;

    constexpr std::int32_t Width() const    { return m_Width; }
    constexpr std::int32_t Height() const   { return m_Height; }
    glm::ivec2 Dimension() const            { return { m_Width, m_Height }; }

private:
    std::uint32_t m_ReferenceID;
    std::int32_t m_Width, m_Height;
    std::int32_t m_Bpp; // # 8-bit components per pixel
    mutable bool m_IsBind;
};

#endif // !RENFERER_TEXTURE_H_
