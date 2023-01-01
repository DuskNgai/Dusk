#include <glad/glad.h>

#include <Dusk/Renderer/OpenGL/OpenGLBuffer.hpp>

DUSK_NAMESPACE_BEGIN

//! OpenGLVertexBuffer
OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
    glCreateBuffers(1, &this->m_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size, float* vertices) {
    glCreateBuffers(1, &this->m_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    glDeleteBuffers(1, &this->m_buffer_id);
}

void OpenGLVertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer_id);
}

void OpenGLVertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(uint32_t size, float* vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
}

void OpenGLVertexBuffer::SetLayout(BufferLayout const& layout) {
    this->m_layout = layout;
}

BufferLayout const& OpenGLVertexBuffer::GetLayout() const {
    return this->m_layout;
}
//! OpenGLVertexBuffer

//! OpenGLIndexBuffer
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t size, uint32_t* indices)
    : m_size(size) {
    glCreateBuffers(1, &this->m_buffer_id);
    // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
    // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
    glBindBuffer(GL_ARRAY_BUFFER, this->m_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    glDeleteBuffers(1, &this->m_buffer_id);
}

void OpenGLIndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_buffer_id);
}

void OpenGLIndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OpenGLIndexBuffer::Size() const {
    return this->m_size;
}
//! OpenGLIndexBuffer

DUSK_NAMESPACE_END
