#ifndef _DUSK_RENDERER_OPENGL_TEXTURE_HPP_
#define _DUSK_RENDERER_OPENGL_TEXTURE_HPP_

#include <utility>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <dusk/renderer/texture.hpp>

DUSK_NAMESPACE_BEGIN

class OpenGLTexture : virtual public Texture {
protected:
    // The default texture in OpenGL is 0.
    uint32_t m_texture_id{ 0 };
    GLenum m_target{ 0 }, m_internal_fmt{ 0 }, m_format{ 0 }, m_data_type{ 0 };

public:
    OpenGLTexture(uint32_t target, uint32_t internal_fmt, uint32_t format, uint32_t data_type);
    virtual ~OpenGLTexture() = default;

    virtual uint32_t get_target() const override;
    virtual uint32_t get_internal_format() const override;
    virtual uint32_t get_format() const override;
    virtual uint32_t get_data_type() const override;
    virtual uint32_t get_texture_id() const override;
    virtual uint32_t get_size_in_bytes() const override;
    virtual uint32_t get_channels() const override;

    virtual void bind(uint32_t slot) const override;
    virtual void unbind() const override;

protected:
    /// @brief Register a texture without specifying its properties and data.
    void register_texture();

    /// @brief Get the number of channels of the specified `format`.
    uint32_t channels(GLenum format) const;

    /// @brief Get the size of the specified `data_type` in bytes.
    uint32_t data_type_size(GLenum data_type) const;
};

/// @class 2D Texture using OpenGL APIs.
/// @see Texture2D
class OpenGLTexture2D : public OpenGLTexture
    , public Texture2D {
private:
    glm::uvec2 m_resolution{ 0, 0 };

public:
    /// @brief Create a texture with the specified `path`.
    // TODO: Currently only supports .png, .jpg, and .bmp.
    // TODO: Support .tiff format, or a image decoder.
    OpenGLTexture2D(std::string const& path);
    /// @brief Create a texture with the specified `width` and `height`.
    /// There is no data inside the texture.
    OpenGLTexture2D(uint32_t width, uint32_t height);
    /// @brief Create a texture with the specified informations.
    /// There is no data inside the texture.
    OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t internal_fmt, uint32_t format, uint32_t data_type);
    virtual ~OpenGLTexture2D();

public:
    virtual uint32_t get_number_of_values() const override;
    virtual uint32_t get_width() const override;
    virtual uint32_t get_height() const override;

    virtual void set_data(void const* data) override;
    virtual void resize(glm::uvec2 new_res) override;

private:
    /// @brief Initialize the texture data with the specified `data`.
    void init(void const* data);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_TEXTURE_HPP_
