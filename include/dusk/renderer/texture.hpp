#ifndef _DUSK_RENDERER_TEXTURE_HPP_
#define _DUSK_RENDERER_TEXTURE_HPP_

#include <memory>
#include <string>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The base class for texture.
/// Texture is sharing once it is created.
class Texture {
public:
    virtual ~Texture() = default;

public:
    /// @brief Get the target of the texture (e.g. GL_TEXTURE_2D).
    virtual uint32_t get_target() const = 0;
    /// @brief Get the internal format of the texture (e.g. GL_RGBA8).
    virtual uint32_t get_internal_format() const = 0;
    /// @brief Get the format of the texture (e.g. GL_RGBA).
    virtual uint32_t get_format() const = 0;
    /// @brief Get the data type of the texture (e.g. GL_UNSIGNED_BYTE).
    virtual uint32_t get_data_type() const = 0;
    virtual uint32_t get_texture_id() const = 0;
    virtual uint32_t get_number_of_values() const = 0;
    virtual uint32_t get_size_in_bytes() const = 0;
    virtual uint32_t get_channels() const = 0;

    /// @param slot The slot of the binding the texture.
    virtual void bind(uint32_t slot) const = 0;
    virtual void unbind() const = 0;

    /// @brief Upload the generated texture to the GPU.
    /// The `size` of the texture should be compatible with the properties of target texture.
    /// E.g. `size` = texture.width * texture.height * texture.channels;
    virtual void set_data(void const* data) = 0;
};

/// @class Once a texture is created, it can be used across multiple renderer processes.
/// So a `shared_ptr` is necessary.
class Texture2D : virtual public Texture {
public:
    /// @brief Create a texture with the specified `path`.
    // TODO: Currently only supports .png, .jpg, and .bmp.
    // TODO: Support .tiff format, or a image decoder.
    static std::shared_ptr<Texture2D> create(std::string const& path);

    /// @brief Create a texture with the specified `width` and `height`.
    /// There is no data inside the texture.
    static std::shared_ptr<Texture2D> create(uint32_t width, uint32_t height);

    /// @brief Create a texture with the specified information.
    /// There is no data inside the texture.
    static std::shared_ptr<Texture2D> create(uint32_t width, uint32_t height, uint32_t internal_format, uint32_t format, uint32_t data_type);

    virtual uint32_t get_width() const = 0;
    virtual uint32_t get_height() const = 0;

    /// @brief Resize the texture to the specified `new_res`.
    virtual void resize(glm::uvec2 new_res) = 0;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_TEXTURE_HPP_
