#include "Texture.h"

#include <Core/Log.h>

#include <glad/glad.h>
#include <stb/stb_image.h>

Texture::Texture(std::string_view _ImagePath) {
    Init(_ImagePath);
}

Texture::~Texture() {
    if (m_ReferenceID)
        Destroy();
}

void Texture::Init(std::string_view _ImagePath) {
    stbi_set_flip_vertically_on_load(true);

    unsigned char* _LocalBuffer = stbi_load(_ImagePath.data(), &m_Width, &m_Height, &m_Bpp, 4);
    if (!_LocalBuffer) {
        CORE_ERROR("Failed to load image: %s\n", _ImagePath.data());
        CORE_ERROR("stb: %s\n", stbi_failure_reason());
        return;
    }

    glGenTextures(1, &m_ReferenceID);
    glBindTexture(GL_TEXTURE_2D, m_ReferenceID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, 0,
        GL_RGBA8, m_Width, m_Height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, static_cast<const void*>(_LocalBuffer));
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(_LocalBuffer);
}

void Texture::Destroy() {
    glDeleteTextures(1, &m_ReferenceID);
    m_ReferenceID   = 0;
    m_Width         = 0;
    m_Height        = 0;
    m_Bpp           = 0;
}

void Texture::Bind(std::uint32_t _TextureUnit) const {
    if (m_IsBind) {
        CORE_WARN("Attempt to bind an already bind Texture.\n");
        return;
    }
    m_IsBind = true;
    glActiveTexture(GL_TEXTURE0 + _TextureUnit);
    glBindTexture(GL_TEXTURE_2D, m_ReferenceID);
}

void Texture::UnBind() const {
    if (!m_IsBind) {
        CORE_WARN("Attempt to unbind an already unbind Texture.\n");
        return;
    }
    m_IsBind = false;
    glBindTexture(GL_TEXTURE_2D, 0);
}
