#include <glad/glad.h>
#include <stb_image.h>

#include <Dusk/Assert.hpp>
#include <Dusk/Log.hpp>
#include <Dusk/Renderer/OpenGL/OpenGLTexture.hpp>

DUSK_NAMESPACE_BEGIN

//! OpenGLTexture
OpenGLTexture::OpenGLTexture(uint32_t target, uint32_t internal_fmt, uint32_t format, uint32_t data_type)
    : m_target(target)
    , m_internal_fmt(internal_fmt)
    , m_format(format)
    , m_data_type(data_type) {
    this->RegisterTexture();
}

uint32_t OpenGLTexture::GetTarget() const { return this->m_target; }

uint32_t OpenGLTexture::GetInternalFormat() const { return this->m_internal_fmt; }

uint32_t OpenGLTexture::GetFormat() const { return this->m_format; }

uint32_t OpenGLTexture::GetDataType() const { return this->m_data_type; }

uint32_t OpenGLTexture::GetTextureID() const { return this->m_texture_id; }

uint32_t OpenGLTexture::GetSizeInBytes() const { return this->Channels(this->GetFormat()) * this->DataTypeSize(this->GetDataType()); }

uint32_t OpenGLTexture::GetChannels() const { return this->Channels(this->GetFormat()); }

void OpenGLTexture::Bind(uint32_t slot) const { glBindTextureUnit(slot, this->GetTextureID()); }

void OpenGLTexture::Unbind() const { glBindTexture(this->GetTarget(), 0); }

void OpenGLTexture::RegisterTexture() {
    glCreateTextures(this->GetTarget(), 1, &this->m_texture_id);
    glTextureParameteri(this->GetTextureID(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(this->GetTextureID(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(this->GetTextureID(), GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(this->GetTextureID(), GL_TEXTURE_WRAP_T, GL_REPEAT);
    this->Unbind();
}

uint32_t OpenGLTexture::Channels(GLenum format) const {
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

uint32_t OpenGLTexture::DataTypeSize(GLenum data_type) const {
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
    : OpenGLTexture(GL_TEXTURE_2D, 0, 0, 0) {
    // Load image data from `path`.
    int w, h, c;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* image_data = stbi_load(path.c_str(), &w, &h, &c, 0);
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

    this->Resize({ w, h });
    this->SetData(image_data);

    // The image data is unused, free it.
    stbi_image_free(image_data);
}

OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
    : OpenGLTexture(GL_TEXTURE_2D, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE)
    , m_resolution({ width, height }) {
    this->Initialize(nullptr);
}

OpenGLTexture2D::~OpenGLTexture2D() {
    // OpenGL silently ignores 0's and names that do not correspond to existing textures.
    // Since we initialize m_texture_id to 0, we can safely call `glDeleteTextures` without checking.
    glDeleteTextures(1, &this->m_texture_id);
}

uint32_t OpenGLTexture2D::GetNumberOfPixels() const { return this->m_resolution[0] * this->m_resolution[1]; }

uint32_t OpenGLTexture2D::GetWidth() const { return this->m_resolution[0]; }

uint32_t OpenGLTexture2D::GetHeight() const { return this->m_resolution[1]; }

void OpenGLTexture2D::SetData(void const* data) {
    this->Bind(0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexSubImage2D(
        GL_TEXTURE_2D, 0, 0, 0,
        this->GetWidth(), this->GetHeight(),
        this->GetFormat(), this->GetDataType(), data
    );
}

void OpenGLTexture2D::Resize(glm::uvec2 new_res) {
    if (new_res == this->m_resolution) {
        return;
    }
    this->m_resolution = new_res;
    this->Initialize(nullptr);
}

void OpenGLTexture2D::Initialize(void const* data) {
    this->Bind(0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(
        GL_TEXTURE_2D, 0, this->GetInternalFormat(),
        this->GetWidth(), this->GetHeight(), 0,
        this->GetFormat(), this->GetDataType(), data
    );
}
//! OpenGLTexture2D

DUSK_NAMESPACE_END
