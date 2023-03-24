#include <glad/glad.h>

#include <dusk/assert.hpp>
#include <dusk/renderer/opengl/opengl-framebuffer.hpp>

DUSK_NAMESPACE_BEGIN

OpenGLFramebuffer::OpenGLFramebuffer(FramebufferProps const& props)
    : m_props{ props }
    , m_color_buffer{ props.Size.x, props.Size.y }
    , m_depth_buffer{ props.Size.x, props.Size.y, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8 } {
    // Bind the color buffer.
    glCreateFramebuffers(1, &this->m_frame_buffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_frame_buffer_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_color_buffer.get_texture_id(), 0);

    // Bind the depth buffer.
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->m_depth_buffer.get_texture_id(), 0);

    // Check if the frame buffer is complete.
    DUSK_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "OpenGLFramebuffer::OpenGLFramebuffer() - Framebuffer is not complete!");

    // Unbind the frame buffer.
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

OpenGLFramebuffer::~OpenGLFramebuffer() {
    glDeleteFramebuffers(1, &this->m_frame_buffer_id);
}

void OpenGLFramebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_frame_buffer_id);
}

void OpenGLFramebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t OpenGLFramebuffer::get_color_attachment() {
    return this->m_color_buffer.get_texture_id();
}

void OpenGLFramebuffer::resize(glm::uvec2 new_size) {
    this->m_color_buffer.resize(new_size);
    this->m_depth_buffer.resize(new_size);
    this->m_props.Size = new_size;
}

void OpenGLFramebuffer::resize(uint32_t width, uint32_t height) {
    this->resize({ width, height });
}

DUSK_NAMESPACE_END
