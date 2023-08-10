#include <glad/gl.h>

#include <dusk/assert.hpp>
#include <dusk/renderer/opengl/opengl-vertex-array.hpp>

DUSK_NAMESPACE_BEGIN

OpenGLVertexArray::OpenGLVertexArray() {
    glCreateVertexArrays(1, &this->m_array_id);
}

OpenGLVertexArray::~OpenGLVertexArray() {
    glDeleteVertexArrays(1, &this->m_array_id);
}

void OpenGLVertexArray::bind() const {
    glBindVertexArray(this->m_array_id);
}

void OpenGLVertexArray::unbind() const {
    glBindVertexArray(0);
}

// clang-format off
static constexpr GLenum shader_data_type_to_opengl_data_type(ShaderDataType type) {
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

void OpenGLVertexArray::add_vertex_buffer(std::shared_ptr<VertexBuffer> const& vertex_buffer) {
    DUSK_CORE_ASSERT(vertex_buffer->get_layout().get_elements().size() > 0, "You should first call the `set_layout` methods of the vertex buffer then add to vertex array!");

    // Bind the vertex array (first) and the vertex buffer (to current vertex array).
    this->bind();
    vertex_buffer->bind();

    // Set the vertex attributes according to its specified layout.
    uint32_t index{ 0 };
    for (auto const& elem : vertex_buffer->get_layout()) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            elem.get_element_count(),
            shader_data_type_to_opengl_data_type(elem.type),
            elem.normalized ? GL_TRUE : GL_FALSE,
            vertex_buffer->get_layout().get_stride(),
            reinterpret_cast<void const*>(static_cast<std::size_t>(elem.offset))
        );
        ++index;
    }
    this->m_vertex_buffers.push_back(vertex_buffer);
}

std::vector<std::shared_ptr<VertexBuffer>> const& OpenGLVertexArray::get_vertex_buffer() const {
    return this->m_vertex_buffers;
}

std::shared_ptr<IndexBuffer> const& OpenGLVertexArray::get_index_buffer() const {
    return this->m_index_buffer;
}

void OpenGLVertexArray::set_index_buffer(std::shared_ptr<IndexBuffer> const& index_buffer) {
    this->bind();
    index_buffer->bind();

    this->m_index_buffer = index_buffer;
}

DUSK_NAMESPACE_END
