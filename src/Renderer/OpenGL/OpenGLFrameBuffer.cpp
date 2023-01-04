#include <glad/glad.h>

#include <Dusk/Assert.hpp>
#include <Dusk/Renderer/OpenGL/OpenGLFrameBuffer.hpp>

DUSK_NAMESPACE_BEGIN

OpenGLFrameBuffer::OpenGLFrameBuffer(FrameBufferProps const& props)
    : m_props(props)
    , m_color_buffer(props.Width, props.Height)
    , m_depth_buffer(props.Width, props.Height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8) {
    // Bind the color buffer.
    glCreateFramebuffers(1, &m_frame_buffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_buffer.GetTextureID(), 0);

    // Bind the depth buffer.
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_buffer.GetTextureID(), 0);

    // Check if the frame buffer is complete.
    DUSK_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "OpenGLFrameBuffer::OpenGLFrameBuffer() - Framebuffer is not complete!");

    // Unbind the frame buffer.
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

OpenGLFrameBuffer::~OpenGLFrameBuffer() {
    glDeleteFramebuffers(1, &m_frame_buffer_id);
}

void OpenGLFrameBuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_id);
}

void OpenGLFrameBuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t OpenGLFrameBuffer::GetColorAttachment() {
    return m_color_buffer.GetTextureID();
}

void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height) {
    (void)width;
    (void)height;
}

DUSK_NAMESPACE_END
