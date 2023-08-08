#ifndef _DUSK_RENDERER_FRAMEBUFFER_HPP_
#define _DUSK_RENDERER_FRAMEBUFFER_HPP_

#include <memory>

#include <glm/glm.hpp>

#include <dusk/common.hpp>
#include <dusk/renderer/texture.hpp>

DUSK_NAMESPACE_BEGIN

enum class AttachmentType {
    None,
    Depth,
    Stencil,
    DepthStencil,
    Color0,
    Color1,
    Color2,
    Color3,
    Color4,
    Color5,
    Color6,
    Color7,
    Color8,
    Color9,
    Color10,
    Color11,
    Color12,
    Color13,
    Color14,
    Color15,
    Color16,
    Color17,
    Color18,
    Color19,
    Color20,
    Color21,
    Color22,
    Color23,
    Color24,
    Color25,
    Color26,
    Color27,
    Color28,
    Color29,
    Color30,
    Color31
};

/// @brief The offline rendering buffer.
class Framebuffer {
public:
    virtual ~Framebuffer() = default;

public:
    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual uint32_t status() const = 0;

    virtual uint32_t get_frame_buffer_id() const = 0;
    virtual std::shared_ptr<Texture2D> get_color_attachment(uint32_t index) const = 0;

    virtual void register_attachment(AttachmentType attachment_id, std::shared_ptr<Texture2D> texture) = 0;
    virtual void unregister_attachment(AttachmentType attachment_id) = 0;

    virtual AttachmentType attach_texture(std::shared_ptr<Texture2D> texture) = 0;
    virtual void attach_texture(AttachmentType attachment_id, std::shared_ptr<Texture2D> texture) = 0;
    virtual void detach_texture(AttachmentType attachment_id) = 0;
    virtual void detach_all_textures() = 0;

    virtual void resize(uint32_t new_width, uint32_t new_height) = 0;

    static std::unique_ptr<Framebuffer> create(uint32_t width, uint32_t height);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_FRAMEBUFFER_HPP_
