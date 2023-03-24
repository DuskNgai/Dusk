#include <dusk/platform-detection.hpp>
#if defined(DUSK_PLATFORM_WINDOWS)
    #include <windows.h>
#endif

#include <glad/glad.h>
#include <stb_image.h>

#include <dusk/assert.hpp>
#include <dusk/log.hpp>
#include <dusk/renderer/opengl/opengl-texture.hpp>

DUSK_NAMESPACE_BEGIN

//! OpenGLTexture
OpenGLTexture::OpenGLTexture(uint32_t target, uint32_t internal_fmt, uint32_t format, uint32_t data_type)
    : m_target{ target }
    , m_internal_fmt{ internal_fmt }
    , m_format{ format }
    , m_data_type{ data_type } {
    this->register_texture();
}

uint32_t OpenGLTexture::get_target() const { return this->m_target; }

uint32_t OpenGLTexture::get_internal_format() const { return this->m_internal_fmt; }

uint32_t OpenGLTexture::get_format() const { return this->m_format; }

uint32_t OpenGLTexture::get_data_type() const { return this->m_data_type; }

uint32_t OpenGLTexture::get_texture_id() const { return this->m_texture_id; }

uint32_t OpenGLTexture::get_size_in_bytes() const { return this->channels(this->get_format()) * this->data_type_size(this->get_data_type()); }

uint32_t OpenGLTexture::get_channels() const { return this->channels(this->get_format()); }

void OpenGLTexture::bind(uint32_t slot) const { glBindTextureUnit(slot, this->get_texture_id()); }

void OpenGLTexture::unbind() const { glBindTexture(this->get_target(), 0); }

void OpenGLTexture::register_texture() {
    glCreateTextures(this->get_target(), 1, &this->m_texture_id);
    glTextureParameteri(this->get_texture_id(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(this->get_texture_id(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(this->get_texture_id(), GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(this->get_texture_id(), GL_TEXTURE_WRAP_T, GL_REPEAT);
    this->unbind();
}

uint32_t OpenGLTexture::channels(GLenum format) const {
    switch (format) {
        case GL_DEPTH_COMPONENT:
        case GL_DEPTH_STENCIL:
        case GL_STENCIL_INDEX:
        case GL_RED:
        case GL_RED_INTEGER:
        case GL_GREEN:
        case GL_GREEN_INTEGER:
        case GL_BLUE:
        case GL_BLUE_INTEGER:
        case GL_ALPHA:
            return 1;

        case GL_RG:
        case GL_RG_INTEGER:
            return 2;

        case GL_RGB:
        case GL_RGB_INTEGER:
        case GL_BGR:
        case GL_BGR_INTEGER:
            return 3;

        case GL_RGBA:
        case GL_RGBA_INTEGER:
        case GL_BGRA:
        case GL_BGRA_INTEGER:
            return 4;

        default:
            DUSK_CORE_ASSERT(false, "Unknown format!");
            return 0;
    }
}

uint32_t OpenGLTexture::data_type_size(GLenum data_type) const {
    switch (data_type) {
        case GL_UNSIGNED_BYTE:
        case GL_BYTE:
            return 1;

        case GL_UNSIGNED_SHORT:
        case GL_SHORT:
        case GL_HALF_FLOAT:
            return 2;

        case GL_UNSIGNED_INT:
        case GL_INT:
        case GL_FLOAT:
            return 4;

        case GL_DOUBLE:
            return 8;

        default:
            DUSK_CORE_ASSERT(false, "Unknown data type!");
            return 0;
    }
}
//! OpenGLTexture

//! OpenGLTexture2D
OpenGLTexture2D::OpenGLTexture2D(std::string const& path)
    : OpenGLTexture{ GL_TEXTURE_2D, 0, 0, 0 } {
    // Load image data from `path`.
    int w, h, c;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* image_data{ stbi_load(path.c_str(), &w, &h, &c, 0) };
    DUSK_CORE_ASSERT(image_data, stbi_failure_reason());

    // Set texture properties by image properties.
    switch (c) {
        case 1:
            this->m_internal_fmt = GL_R8;
            this->m_format = GL_RED;
            break;

        case 2:
            this->m_internal_fmt = GL_RG8;
            this->m_format = GL_RG;
            break;

        case 3:
            this->m_internal_fmt = GL_RGB8;
            this->m_format = GL_RGB;
            break;

        case 4:
            this->m_internal_fmt = GL_RGBA8;
            this->m_format = GL_RGBA;
            break;

        default:
            DUSK_CORE_ASSERT(false, "Unknown number of channels!");
            break;
    }
    this->m_data_type = GL_UNSIGNED_BYTE;

    this->resize({ w, h });
    this->set_data(image_data);

    // The image data is unused, free it.
    stbi_image_free(image_data);
}

OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
    : OpenGLTexture2D(width, height, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE) {}

OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t internal_fmt, uint32_t format, uint32_t data_type)
    : OpenGLTexture{ GL_TEXTURE_2D, internal_fmt, format, data_type }
    , m_resolution({ width, height }) {
    this->init(nullptr);
}

OpenGLTexture2D::~OpenGLTexture2D() {
    // OpenGL silently ignores 0's and names that do not correspond to existing textures.
    // Since we initialize m_texture_id to 0, we can safely call `glDeleteTextures` without checking.
    glDeleteTextures(1, &this->m_texture_id);
}

uint32_t OpenGLTexture2D::get_number_of_values() const { return this->m_resolution[0] * this->m_resolution[1]; }

uint32_t OpenGLTexture2D::get_width() const { return this->m_resolution[0]; }

uint32_t OpenGLTexture2D::get_height() const { return this->m_resolution[1]; }

void OpenGLTexture2D::set_data(void const* data) {
    this->bind(0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexSubImage2D(
        GL_TEXTURE_2D, 0, 0, 0,
        this->get_width(), this->get_height(),
        this->get_format(), this->get_data_type(), data
    );
}

void OpenGLTexture2D::resize(glm::uvec2 new_res) {
    if (new_res == this->m_resolution) {
        return;
    }
    this->m_resolution = new_res;
    this->init(nullptr);
}

void OpenGLTexture2D::init(void const* data) {
    this->bind(0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(
        GL_TEXTURE_2D, 0, this->get_internal_format(),
        this->get_width(), this->get_height(), 0,
        this->get_format(), this->get_data_type(), data
    );
}
//! OpenGLTexture2D

DUSK_NAMESPACE_END
