#ifndef _DUSK_RENDERER_VERTEX_ARRAY_HPP_
#define _DUSK_RENDERER_VERTEX_ARRAY_HPP_

#include <Dusk/Renderer/Buffer.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The interface class for renderer and rendering API related to vertex array.
class VertexArray {
public:
    virtual ~VertexArray() = default;

public:
    static std::unique_ptr<VertexArray> Create();

    /// @brief Bind the buffer for rendering.
    virtual void Bind() const = 0;

    /// @brief Unbind the buffer for stoping rendering.
    virtual void Unbind() const = 0;

    /// @brief Manage a vertex buffer.
    virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> const& vertex_buffer) = 0;

    /// @brief Get vertex buffers.
    virtual std::vector<std::shared_ptr<VertexBuffer>> const& GetVertexBuffers() const = 0;

    /// @brief Manage a index buffer.
    virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> const& index_buffer) = 0;

    /// @brief Get vertex buffers.
    virtual std::shared_ptr<IndexBuffer> const& GetIndexBuffer() const = 0;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_VERTEX_ARRAY_HPP_
