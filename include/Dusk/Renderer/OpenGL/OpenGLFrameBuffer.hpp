#ifndef _DUSK_RENDERER_OPENGL_FRAME_BUFFER_HPP_
#define _DUSK_RENDERER_OPENGL_FRAME_BUFFER_HPP_

#include <Dusk/Renderer/FrameBuffer.hpp>
#include <Dusk/Renderer/OpenGL/OpenGLTexture.hpp>

DUSK_NAMESPACE_BEGIN

class OpenGLFrameBuffer : public FrameBuffer {
private:
    FrameBufferProps m_props;
    OpenGLTexture2D m_color_buffer;
    OpenGLTexture2D m_depth_buffer;
    uint32_t m_frame_buffer_id{0};

public:
    OpenGLFrameBuffer(FrameBufferProps const& props);
    virtual ~OpenGLFrameBuffer();

public:
    void Bind() override;
    void Unbind() override;

    uint32_t GetColorAttachment() override;

    void Resize(uint32_t width, uint32_t height) override;
};

DUSK_NAMESPACE_END

#endif
