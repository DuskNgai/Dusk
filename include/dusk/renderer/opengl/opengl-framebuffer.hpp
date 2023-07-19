#ifndef _DUSK_RENDERER_OPENGL_FRAME_BUFFER_HPP_
#define _DUSK_RENDERER_OPENGL_FRAME_BUFFER_HPP_

#include <vector>

#include <dusk/renderer/framebuffer.hpp>
#include <dusk/renderer/opengl/opengl-texture.hpp>

DUSK_NAMESPACE_BEGIN

class OpenGLFramebuffer : public Framebuffer {
private:
    uint32_t m_frame_buffer_id{ 0 };
    FramebufferProps m_props;

    std::vector<uint32_t> m_color_attachments;
    uint32_t m_depth_attachment{ 0 };
    uint32_t m_stencil_attachment{ 0 };

public:
    OpenGLFramebuffer();
    virtual ~OpenGLFramebuffer();

public:
    virtual void bind() override;
    virtual void unbind() override;
    virtual uint32_t status() const override;

    virtual uint32_t get_frame_buffer_id() const override;
    virtual uint32_t get_color_attachment_id(uint32_t index) const override;

    virtual AttachmentType attach_texture(std::shared_ptr<Texture> texture) override;
    virtual void attach_texture(AttachmentType attachment_id, std::shared_ptr<Texture> texture) override;
    virtual void detach_texture(AttachmentType attachment_id) override;
    virtual void detach_all_textures() override;

    // virtual void resize(glm::uvec2 new_size) override;
    // virtual void resize(uint32_t width, uint32_t height) override;

private:
    static uint32_t get_max_color_attachments();
    static uint32_t id_to_num(AttachmentType id);
    static AttachmentType num_to_id(uint32_t num);

    AttachmentType get_next_color_attachment() const;

    virtual void register_attachment(AttachmentType attachment_id, uint32_t tex_id) override;
    virtual void unregister_attachment(AttachmentType attachment_id) override;
};

DUSK_NAMESPACE_END

#endif
