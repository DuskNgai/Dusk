#include <glad/glad.h>

#include <Dusk/Assert.hpp>
#include <Dusk/Renderer/OpenGL/OpenGLVertexArray.hpp>

DUSK_NAMESPACE_BEGIN

OpenGLVertexArray::OpenGLVertexArray() {
    glGenVertexArrays(1, &this->m_array_id);
}

OpenGLVertexArray::~OpenGLVertexArray() {
    glDeleteVertexArrays(1, &this->m_array_id);
}

void OpenGLVertexArray::Bind() const {
    glBindVertexArray(this->m_array_id);
}

void OpenGLVertexArray::Unbind() const {
    glBindVertexArray(0);
}

// clang-format off
static constexpr GLenum ShaderDataType2OpenGLDataType(ShaderDataType type) {
    switch(type) {
        case ShaderDataType::Float:  return GL_FLOAT;
        case ShaderDataType::Vec2:   return GL_FLOAT;
        case ShaderDataType::Vec3:   return GL_FLOAT;
        case ShaderDataType::Vec4:   return GL_FLOAT;
        case ShaderDataType::Int:    return GL_INT;
        case ShaderDataType::Ivec2:  return GL_INT;
        case ShaderDataType::Ivec3:  return GL_INT;
        case ShaderDataType::Ivec4:  return GL_INT;
        case ShaderDataType::Uint:   return GL_UNSIGNED_INT;
        case ShaderDataType::Uvec2:  return GL_UNSIGNED_INT;
        case ShaderDataType::Uvec3:  return GL_UNSIGNED_INT;
        case ShaderDataType::Uvec4:  return GL_UNSIGNED_INT;
        case ShaderDataType::Bool:   return GL_BOOL;
        case ShaderDataType::Mat2:   return GL_FLOAT;
        case ShaderDataType::Mat3:   return GL_FLOAT;
        case ShaderDataType::Mat4:   return GL_FLOAT;
        default: DUSK_CORE_ASSERT(false, "Unrecognized ShaderDataType."); return GL_ZERO;
    }
}
// clang-format on

void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> const& vertex_buffer) {
    DUSK_CORE_ASSERT(vertex_buffer->GetLayout().GetElements().size() > 0, "You should first call the `SetLayout` methods of the vertex buffer then add to vertex array!");

    // Bind the vertex array (first) and the vertex buffer (to current vertex array).
    this->Bind();
    vertex_buffer->Bind();

    // Set the vertex attributes according to its specified layout.
    uint32_t index{0};
    for (auto const& elem : vertex_buffer->GetLayout()) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index, elem.GetElementCount(),
            ShaderDataType2OpenGLDataType(elem.type),
            elem.normalized ? GL_TRUE : GL_FALSE,
            vertex_buffer->GetLayout().GetStride(), (void const*)static_cast<std::size_t>(elem.offset)
        );
        ++index;
    }
    this->m_vertex_buffers.push_back(vertex_buffer);
}

std::vector<std::shared_ptr<VertexBuffer>> const& OpenGLVertexArray::GetVertexBuffers() const {
    return this->m_vertex_buffers;
}

std::shared_ptr<IndexBuffer> const& OpenGLVertexArray::GetIndexBuffer() const {
    return this->m_index_buffer;
}

void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> const& index_buffer) {
    this->Bind();
    index_buffer->Bind();

    this->m_index_buffer = index_buffer;
}

DUSK_NAMESPACE_END
