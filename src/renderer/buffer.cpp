#include <dusk/assert.hpp>
#include <dusk/renderer/renderer-API.hpp>
#include <dusk/renderer/opengl/opengl-buffer.hpp>

DUSK_NAMESPACE_BEGIN

//! BufferElement

// clang-format off
/// @brief Simply get the size of the shader data type.
static constexpr uint32_t get_shader_data_type_size(ShaderDataType type) {
    switch (type) {
        case ShaderDataType::Float:  return sizeof(float);
        case ShaderDataType::Vec2:   return sizeof(float) * 2;
        case ShaderDataType::Vec3:   return sizeof(float) * 3;
        case ShaderDataType::Vec4:   return sizeof(float) * 4;
        case ShaderDataType::Int:    return sizeof(int);
        case ShaderDataType::Ivec2:  return sizeof(int) * 2;
        case ShaderDataType::Ivec3:  return sizeof(int) * 3;
        case ShaderDataType::Ivec4:  return sizeof(int) * 4;
        case ShaderDataType::Uint:   return sizeof(unsigned);
        case ShaderDataType::Uvec2:  return sizeof(unsigned) * 2;
        case ShaderDataType::Uvec3:  return sizeof(unsigned) * 3;
        case ShaderDataType::Uvec4:  return sizeof(unsigned) * 4;
        case ShaderDataType::Bool:   return sizeof(bool);
        case ShaderDataType::Mat2:   return sizeof(float) * 2 * 2;
        case ShaderDataType::Mat3:   return sizeof(float) * 3 * 3;
        case ShaderDataType::Mat4:   return sizeof(float) * 4 * 4;
        default: DUSK_CORE_ASSERT(false, "Unrecognized ShaderDataType."); return 0;
    }
}
// clang-format on

BufferElement::BufferElement(ShaderDataType type, std::string const& name, bool normalized)
    : type{ type }
    , name{ name }
    , size{ get_shader_data_type_size(type) }
    , normalized{ normalized } {}

// clang-format off
// The required size/count should only be 1, 2, 3, 4.
int32_t BufferElement::get_element_count() const {
    switch (this->type) {
        case ShaderDataType::Float:  return 1;
        case ShaderDataType::Vec2:   return 2;
        case ShaderDataType::Vec3:   return 3;
        case ShaderDataType::Vec4:   return 4;
        case ShaderDataType::Int:    return 1;
        case ShaderDataType::Ivec2:  return 2;
        case ShaderDataType::Ivec3:  return 3;
        case ShaderDataType::Ivec4:  return 4;
        case ShaderDataType::Uint:   return 1;
        case ShaderDataType::Uvec2:  return 2;
        case ShaderDataType::Uvec3:  return 3;
        case ShaderDataType::Uvec4:  return 4;
        case ShaderDataType::Bool:   return 1;
        case ShaderDataType::Mat2:   return 2; // 2 * vec2
        case ShaderDataType::Mat3:   return 3; // 3 * vec3
        case ShaderDataType::Mat4:   return 4; // 4 * vec4
        default: DUSK_CORE_ASSERT(false, "Unrecognized ShaderDataType."); return 0;
    }
}
// clang-format on
//! BufferElement

//! BufferLayout
BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
    : m_total_size{ 0 }
    , m_elements{ elements } {
    this->calculate_offset();
}

uint32_t BufferLayout::GetStride() const { return this->m_total_size; }

std::vector<BufferElement> const& BufferLayout::get_elements() const {
    return this->m_elements;
}

std::vector<BufferElement>::iterator BufferLayout::begin() { return this->m_elements.begin(); }
std::vector<BufferElement>::iterator BufferLayout::end() { return this->m_elements.end(); }
std::vector<BufferElement>::const_iterator BufferLayout::begin() const { return this->m_elements.begin(); }
std::vector<BufferElement>::const_iterator BufferLayout::end() const { return this->m_elements.end(); }

void BufferLayout::calculate_offset() {
    uint32_t offset{ 0 };
    for (auto&& elem : this->m_elements) {
        elem.offset = offset;
        offset += elem.size;
    }
    this->m_total_size = offset;
}
//! BufferLayout

// clang-format off
//! VertexBuffer
std::shared_ptr<VertexBuffer> VertexBuffer::create(uint32_t size_in_bytes) {
    switch (RendererAPI::get_API()) {
        case RendererAPI::API::None:      DUSK_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLVertexBuffer>(size_in_bytes);
        case RendererAPI::API::Vulkan:    DUSK_CORE_ASSERT(false, "RendererAPI::API::Vulkan is currently not supported!"); return nullptr;
        case RendererAPI::API::DirectX12: DUSK_CORE_ASSERT(false, "RendererAPI::API::DirectX12 is currently not supported!"); return nullptr;
        default: DUSK_CORE_ASSERT(false, "Unrecognized RendererAPI::API!"); return nullptr;
    }
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(uint32_t size_in_bytes, float const* vertices) {
    switch (RendererAPI::get_API()) {
        case RendererAPI::API::None:      DUSK_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLVertexBuffer>(size_in_bytes, vertices);
        case RendererAPI::API::Vulkan:    DUSK_CORE_ASSERT(false, "RendererAPI::API::Vulkan is currently not supported!"); return nullptr;
        case RendererAPI::API::DirectX12: DUSK_CORE_ASSERT(false, "RendererAPI::API::DirectX12 is currently not supported!"); return nullptr;
        default: DUSK_CORE_ASSERT(false, "Unrecognized RendererAPI::API!"); return nullptr;
    }
}
//! VertexBuffer

//! IndexBuffer
std::shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t size_in_bytes, uint32_t const* indices) {
    switch (RendererAPI::get_API()) {
        case RendererAPI::API::None:      DUSK_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLIndexBuffer>(size_in_bytes, indices);
        case RendererAPI::API::Vulkan:    DUSK_CORE_ASSERT(false, "RendererAPI::API::Vulkan is currently not supported!"); return nullptr;
        case RendererAPI::API::DirectX12: DUSK_CORE_ASSERT(false, "RendererAPI::API::DirectX12 is currently not supported!"); return nullptr;
        default: DUSK_CORE_ASSERT(false, "Unrecognized RendererAPI::API!"); return nullptr;
    }
}
//! IndexBuffer
// clang-format on

DUSK_NAMESPACE_END
