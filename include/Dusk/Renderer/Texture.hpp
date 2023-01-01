#ifndef _DUSK_RENDERER_TEXTURE_HPP_
#define _DUSK_RENDERER_TEXTURE_HPP_

#include <memory>
#include <string>

#include <Dusk/Common.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The base class for texture.
/// Texture is sharing once it is created.
class Texture {
public:
    virtual ~Texture() = default;

public:
    /// @brief Get the target of the texture (e.g. GL_TEXTURE_2D).
    virtual uint32_t GetTarget() const = 0;
    /// @brief Get the internal format of the texture (e.g. GL_RGBA8).
    virtual uint32_t GetInternalFormat() const = 0;
    /// @brief Get the format of the texture (e.g. GL_RGBA).
    virtual uint32_t GetFormat() const = 0;
    /// @brief Get the data type of the texture (e.g. GL_UNSIGNED_BYTE).
    virtual uint32_t GetDataType() const = 0;
    /// @brief Get the id of the texture.
    virtual uint32_t GetTextureID() const = 0;
    /// @brief Get the number of pixels of the texture.
    virtual uint32_t GetNumberOfPixels() const = 0;
    /// @brief Get the size of the texture.
    virtual uint32_t GetSizeInBytes() const = 0;
    /// @brief Get the number of channels of the texture.
    virtual uint32_t GetChannels() const = 0;

    /// @brief Bind the texture for shader.
    /// @param slot The slot of the binding the texture.
    virtual void Bind(uint32_t slot) const = 0;
    /// @brief Unbind the texture for other usage.
    virtual void Unbind() const = 0;

    /// @brief Upload the generated texture to the GPU.
    /// The `size` of the texture should be compatible with the properties of target texture.
    /// E.g. `size` = texture.width * texture.height * texture.channels;
    virtual void SetData(void const* data) = 0;
};

/// @class Once a texture is created, it can be used across multiple renderer processes.
/// So a `shared_ptr` is necessary.
class Texture2D : virtual public Texture {
public:
    /// @brief Create a texture with the specified `path`.
    // TODO: Currently only supports .png, .jpg, and .bmp.
    // TODO: Support .tiff format, or a image decoder.
    static std::shared_ptr<Texture2D> Create(std::string const& path);
    /// @brief Create a texture with the specified `width` and `height`.
    /// There is no data inside the texture.
    static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height);

    /// @brief Get the width of the texture.
    virtual uint32_t GetWidth() const = 0;
    /// @brief Get the height of the texture.
    virtual uint32_t GetHeight() const = 0;

    /// @brief Resize the texture to the specified `new_res`.
    virtual void Resize(glm::uvec2 new_res) = 0;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_TEXTURE_HPP_
