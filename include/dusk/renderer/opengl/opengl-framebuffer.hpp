#ifndef _DUSK_RENDERER_OPENGL_FRAME_BUFFER_HPP_
#define _DUSK_RENDERER_OPENGL_FRAME_BUFFER_HPP_

#include <dusk/renderer/framebuffer.hpp>
#include <dusk/renderer/opengl/opengl-texture.hpp>

DUSK_NAMESPACE_BEGIN

class OpenGLFramebuffer : public Framebuffer {
private:
    FramebufferProps m_props;
    OpenGLTexture2D m_color_buffer;
    OpenGLTexture2D m_depth_buffer;
    uint32_t m_frame_buffer_id{ 0 };

public:
    OpenGLFramebuffer(FramebufferProps const& props);
    virtual ~OpenGLFramebuffer();

public:
    virtual void bind() override;
    virtual void unbind() override;

    virtual uint32_t get_color_attachment() override;

    virtual void resize(glm::uvec2 new_size) override;
    virtual void resize(uint32_t width, uint32_t height) override;
};

DUSK_NAMESPACE_END

#endif
