#ifndef _DUSK_RENDERER_OPENGL_TEXTURE_HPP_
#define _DUSK_RENDERER_OPENGL_TEXTURE_HPP_

#include <array>
#include <utility>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Dusk/Renderer/Texture.hpp>

DUSK_NAMESPACE_BEGIN

class OpenGLTexture : virtual public Texture {
protected:
    // The default texture in OpenGL is 0.
    uint32_t m_texture_id{0};
    GLenum m_target{0}, m_internal_fmt{0}, m_format{0}, m_data_type{0};

public:
    OpenGLTexture(uint32_t target, uint32_t internal_fmt, uint32_t format, uint32_t data_type);

    uint32_t GetTarget() const override;
    uint32_t GetInternalFormat() const override;
    uint32_t GetFormat() const override;
    uint32_t GetDataType() const override;
    uint32_t GetTextureID() const override;
    uint32_t GetSizeInBytes() const override;
    uint32_t GetChannels() const override;

    virtual void Bind(uint32_t slot) const override;
    virtual void Unbind() const override;

protected:
    /// @brief Register a texture without specifying its properties and data.
    void RegisterTexture();
    /// @brief Get the number of channels of the specified `format`.
    uint32_t Channels(GLenum format) const;
    /// @brief Get the size of the specified `data_type` in bytes.
    uint32_t DataTypeSize(GLenum data_type) const;
};

/// @class 2D Texture using OpenGL APIs.
/// @see Texture2D
class OpenGLTexture2D : public OpenGLTexture, public Texture2D {
private:
    glm::uvec2 m_resolution{0, 0};

public:
    /// @brief Create a texture with the specified `path`.
    // TODO: Currently only supports .png, .jpg, and .bmp.
    // TODO: Support .tiff format, or a image decoder.
    OpenGLTexture2D(std::string const& path);
    /// @brief Create a texture with the specified `width` and `height`.
    /// There is no data inside the texture.
    OpenGLTexture2D(uint32_t width, uint32_t height);
    virtual ~OpenGLTexture2D();

    virtual uint32_t GetNumberOfPixels() const override;
    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;

    virtual void SetData(void const* data) override;
    virtual void Resize(glm::uvec2 new_res) override;

private:
    /// @brief Initialize the texture data with the specified `data`.
    void Initialize(void const* data);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_TEXTURE_HPP_
