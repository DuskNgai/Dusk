#ifndef _DUSK_RENDERER_BUFFER_HPP_
#define _DUSK_RENDERER_BUFFER_HPP_

#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include <Dusk/Common.hpp>

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
    uint32_t offset{0};
    bool normalized{false};

public:
    BufferElement() = default;
    BufferElement(ShaderDataType type, std::string const& name);

public:
    /// @brief Count the number of the basic data type of a complex data type.
    /// E.g. a vec4 consists of `4` float.
    int32_t GetElementCount() const;
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
    std::vector<BufferElement> const& GetElements() const;

    std::vector<BufferElement>::iterator begin();
    std::vector<BufferElement>::iterator end();
    std::vector<BufferElement>::const_iterator begin() const;
    std::vector<BufferElement>::const_iterator end() const;

private:
    /// @brief Calculate the offset of the vertex layout.
    void CalculateOffset();
};

/// @class The interface class for renderer and rendering API related to vertex buffer.
class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

public:
    /// @brief Used for batch rendering.
    /// @param size The size of the buffer in bytes.
    static std::shared_ptr<VertexBuffer> Create(uint32_t size);

    /// @brief Used for rendering a single object.
    /// @param size The size of the buffer in bytes.
    /// @param vertices The vertices to be rendered.
    static std::shared_ptr<VertexBuffer> Create(uint32_t size, float* vertices);

    /// @brief Bind the buffer for rendering.
    virtual void Bind() const = 0;

    /// @brief Unbind the buffer for stoping rendering.
    virtual void Unbind() const = 0;

    /// @brief Set new data for rendering, commly used for batch rendering.
    virtual void SetData(uint32_t size, float* vertices) = 0;

    /// @brief Set the layout of the data in the vertex buffer.
    virtual void SetLayout(BufferLayout const& layout) = 0;

    /// @brief Get the layout of the data in the vertex buffer.
    virtual BufferLayout const& GetLayout() const = 0;
};

/// @class The interface class for renderer and rendering API related to index buffer.
class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

public:
    static std::shared_ptr<IndexBuffer> Create(uint32_t size, uint32_t* indices);

    /// @brief Bind the buffer for rendering.
    virtual void Bind() const = 0;

    /// @brief Unbind the buffer for stoping rendering.
    virtual void Unbind() const = 0;

    /// @brief The size of the index buffer in the number of indices.
    virtual uint32_t Size() const = 0;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_BUFFER_HPP_
