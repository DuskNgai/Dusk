#ifndef _DUSK_RENDERER_BUFFER_HPP_
#define _DUSK_RENDERER_BUFFER_HPP_

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

/// @class Existing shader data types.
// clang-format off
enum class ShaderDataType {
    None = 0,
    Float, Vec2, Vec3, Vec4,
    Int, Ivec2, Ivec3, Ivec4,
    Uint, Uvec2, Uvec3, Uvec4,
    Bool, Bvec2, Bvec3, Bvec4,
    Mat2, Mat3, Mat4
};
// clang-format on

/// @class The information of the vertex buffer data.
struct BufferElement {
public:
    ShaderDataType type;
    std::string name;
    uint32_t size;
    uint32_t offset{ 0 };
    bool normalized;

public:
    BufferElement() = default;
    BufferElement(ShaderDataType type, std::string const& name, bool normalized = false);

public:
    /// @brief Count the number of the basic data type of a complex data type.
    /// E.g. a vec4 consists of `4` float.
    int32_t get_element_count() const;
};

/// @class The unity of the information of the vertex buffer data.
class BufferLayout {
private:
    uint32_t m_total_size;
    std::vector<BufferElement> m_elements;

public:
    BufferLayout() = default;
    BufferLayout(std::initializer_list<BufferElement> elements);

public:
    /// @brief The stride is the total size of one vertex information.
    uint32_t GetStride() const;

    /// @brief Get the exactly vertex information.
    std::vector<BufferElement> const& get_elements() const;

    std::vector<BufferElement>::iterator begin();
    std::vector<BufferElement>::iterator end();
    std::vector<BufferElement>::const_iterator begin() const;
    std::vector<BufferElement>::const_iterator end() const;

private:
    /// @brief Calculate the offset of the vertex layout.
    void calculate_offset();
};

/// @class The interface class for renderer and rendering API related to vertex buffer.
class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

public:
    virtual void bind() const = 0;

    virtual void unbind() const = 0;

    /// @brief Set new data for rendering, commly used for batch rendering.
    virtual void set_data(uint32_t size, float* vertices) = 0;

    /// @brief Set the layout of the data in the vertex buffer.
    virtual void set_layout(BufferLayout const& layout) = 0;

    /// @brief Get the layout of the data in the vertex buffer.
    virtual BufferLayout const& get_layout() const = 0;

    static std::shared_ptr<VertexBuffer> create(uint32_t size);

    static std::shared_ptr<VertexBuffer> create(uint32_t size, float* vertices);
};

/// @class The interface class for renderer and rendering API related to index buffer.
class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

public:
    virtual void bind() const = 0;

    virtual void unbind() const = 0;

    /// @brief The size of the index buffer in the number of indices.
    virtual uint32_t size() const = 0;

    static std::shared_ptr<IndexBuffer> create(uint32_t size, uint32_t* indices);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_BUFFER_HPP_
