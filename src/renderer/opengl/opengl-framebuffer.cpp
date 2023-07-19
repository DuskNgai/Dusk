#include <algorithm>

#include <glad/gl.h>

#include <dusk/assert.hpp>
#include <dusk/renderer/opengl/opengl-framebuffer.hpp>

DUSK_NAMESPACE_BEGIN

static constexpr uint32_t get_attachment_type(AttachmentType type) {
    switch (type) {
        case AttachmentType::None: return 0;
        case AttachmentType::Depth: return GL_DEPTH_ATTACHMENT;
        case AttachmentType::Stencil: return GL_STENCIL_ATTACHMENT;
        case AttachmentType::DepthStencil: return GL_DEPTH_STENCIL_ATTACHMENT;
        case AttachmentType::Color0: return GL_COLOR_ATTACHMENT0;
        case AttachmentType::Color1:
        case AttachmentType::Color2:
        case AttachmentType::Color3:
        case AttachmentType::Color4:
        case AttachmentType::Color5:
        case AttachmentType::Color6:
        case AttachmentType::Color7:
        case AttachmentType::Color8:
        case AttachmentType::Color9:
        case AttachmentType::Color10:
        case AttachmentType::Color11:
        case AttachmentType::Color12:
        case AttachmentType::Color13:
        case AttachmentType::Color14:
        case AttachmentType::Color15:
        case AttachmentType::Color16:
        case AttachmentType::Color17:
        case AttachmentType::Color18:
        case AttachmentType::Color19:
        case AttachmentType::Color20:
        case AttachmentType::Color21:
        case AttachmentType::Color22:
        case AttachmentType::Color23:
        case AttachmentType::Color24:
        case AttachmentType::Color25:
        case AttachmentType::Color26:
        case AttachmentType::Color27:
        case AttachmentType::Color28:
        case AttachmentType::Color29:
        case AttachmentType::Color30:
        case AttachmentType::Color31:
            return GL_COLOR_ATTACHMENT0 + static_cast<uint32_t>(type) - static_cast<uint32_t>(AttachmentType::Color0);
        default: DUSK_ASSERT(false, "Invalid attachment type"); return 0;
    }
}

OpenGLFramebuffer::OpenGLFramebuffer() {
    glCreateFramebuffers(1, &this->m_frame_buffer_id);
    this->m_color_attachments.resize(OpenGLFramebuffer::get_max_color_attachments(), 0);
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

uint32_t OpenGLFramebuffer::status() const {
    return glCheckFramebufferStatus(GL_FRAMEBUFFER);
}

uint32_t OpenGLFramebuffer::get_frame_buffer_id() const {
    return this->m_frame_buffer_id;
}

uint32_t OpenGLFramebuffer::get_color_attachment_id(uint32_t index) const {
    DUSK_ASSERT(index < this->m_color_attachments.size(), "Invalid color attachment index");
    return this->m_color_attachments[index];
}

AttachmentType OpenGLFramebuffer::attach_texture(std::shared_ptr<Texture> texture) {
    auto attachment_id{ this->get_next_color_attachment() };
    this->register_attachment(attachment_id, texture->get_texture_id());
    glFramebufferTexture2D(GL_FRAMEBUFFER, get_attachment_type(attachment_id), GL_TEXTURE_2D, texture->get_texture_id(), 0);
    return attachment_id;
}

void OpenGLFramebuffer::attach_texture(AttachmentType attachment_id, std::shared_ptr<Texture> texture) {
    this->register_attachment(attachment_id, texture->get_texture_id());
    glFramebufferTexture2D(GL_FRAMEBUFFER, get_attachment_type(attachment_id), GL_TEXTURE_2D, texture->get_texture_id(), 0);
}

void OpenGLFramebuffer::detach_texture(AttachmentType attachment_id) {
    this->unregister_attachment(attachment_id);
    glFramebufferTexture(GL_FRAMEBUFFER, get_attachment_type(attachment_id), 0, 0);
}

void OpenGLFramebuffer::detach_all_textures() {
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 0, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, 0, 0);
    this->m_depth_attachment = 0;
    this->m_stencil_attachment = 0;

    for (GLuint num = 0; num < this->m_color_attachments.size(); ++num) {
        if (this->m_color_attachments[num] != 0) {
            glFramebufferTexture(GL_FRAMEBUFFER, get_attachment_type(OpenGLFramebuffer::num_to_id(num)), 0, 0);
            this->m_color_attachments[num] = 0;
        }
    }
}

// void OpenGLFramebuffer::resize(glm::uvec2 new_size) {
//     if (this->m_frame_buffer_id) {
//         glDeleteFramebuffers(1, &this->m_frame_buffer_id);
//         glDeleteTextures(1, &this->m_color_attachment);
//         glDeleteTextures(1, &this->m_depth_attachment);

//         this->m_color_attachment = 0;
//         this->m_depth_attachment = 0;
//     }

//     glCreateFramebuffers(1, &this->m_frame_buffer_id);
//     this->bind();

//     this->m_props.Size = new_size;
// }

// void OpenGLFramebuffer::resize(uint32_t width, uint32_t height) {
//     this->resize({ width, height });
// }

uint32_t OpenGLFramebuffer::get_max_color_attachments() {
    int32_t max_color_attachments;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &max_color_attachments);
    return static_cast<uint32_t>(max_color_attachments);
}

uint32_t OpenGLFramebuffer::id_to_num(AttachmentType id) {
    return static_cast<uint32_t>(id) - static_cast<uint32_t>(AttachmentType::Color0);
}

AttachmentType OpenGLFramebuffer::num_to_id(uint32_t num) {
    return static_cast<AttachmentType>(static_cast<uint32_t>(AttachmentType::Color0) + num);
}

AttachmentType OpenGLFramebuffer::get_next_color_attachment() const {
    auto it = std::find(this->m_color_attachments.begin(), this->m_color_attachments.end(), 0);
    DUSK_ASSERT(it != this->m_color_attachments.end(), "No more color attachments available");
    return OpenGLFramebuffer::num_to_id(static_cast<GLuint>(std::distance(this->m_color_attachments.begin(), it)));
}

void OpenGLFramebuffer::register_attachment(AttachmentType attachment_id, GLuint tex_id) {
    if (attachment_id == AttachmentType::Depth) {
        this->m_depth_attachment = tex_id;
    }
    else if (attachment_id == AttachmentType::Stencil) {
        this->m_stencil_attachment = tex_id;
    }
    else if (attachment_id == AttachmentType::DepthStencil) {
        this->m_depth_attachment = tex_id;
        this->m_stencil_attachment = tex_id;
    }
    else {
        auto color_attachment_index{ OpenGLFramebuffer::id_to_num(attachment_id) };
        DUSK_ASSERT(color_attachment_index < OpenGLFramebuffer::get_max_color_attachments(), "Invalid color attachment index");
        this->m_color_attachments[color_attachment_index] = tex_id;
    }
}

void OpenGLFramebuffer::unregister_attachment(AttachmentType attachment_id) {
    this->register_attachment(attachment_id, 0);
}

DUSK_NAMESPACE_END
