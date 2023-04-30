#include <glad/glad.h>

#include <dusk/renderer/opengl/opengl-buffer.hpp>

DUSK_NAMESPACE_BEGIN

//! OpenGLVertexBuffer
OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size_in_bytes) {
    glCreateBuffers(1, &this->m_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size_in_bytes, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size_in_bytes, float const* vertices) {
    glCreateBuffers(1, &this->m_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size_in_bytes, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    glDeleteBuffers(1, &this->m_buffer_id);
}

void OpenGLVertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer_id);
}

void OpenGLVertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::set_data(uint32_t size_in_bytes, float const* vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size_in_bytes, vertices);
}

void OpenGLVertexBuffer::set_layout(BufferLayout const& layout) {
    this->m_layout = layout;
}

BufferLayout const& OpenGLVertexBuffer::get_layout() const {
    return this->m_layout;
}
//! OpenGLVertexBuffer

//! OpenGLIndexBuffer
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t size_in_bytes, uint32_t const* indices)
    : m_size{ size_in_bytes / static_cast<uint32_t>(sizeof(uint32_t)) } {
    glCreateBuffers(1, &this->m_buffer_id);
    // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
    // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
    glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size_in_bytes, indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    glDeleteBuffers(1, &this->m_buffer_id);
}

void OpenGLIndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_buffer_id);
}

void OpenGLIndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OpenGLIndexBuffer::size() const {
    return this->m_size;
}
//! OpenGLIndexBuffer

DUSK_NAMESPACE_END
