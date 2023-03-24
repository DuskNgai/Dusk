#ifndef _DUSK_RENDERER_VERTEX_ARRAY_HPP_
#define _DUSK_RENDERER_VERTEX_ARRAY_HPP_

#include <dusk/renderer/buffer.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The interface class for renderer and rendering API related to vertex array.
class VertexArray {
public:
    virtual ~VertexArray() = default;

public:
    /// @brief Bind the buffer for rendering.
    virtual void bind() const = 0;

    /// @brief Unbind the buffer for stoping rendering.
    virtual void unbind() const = 0;

    /// @brief Manage a vertex buffer.
    virtual void add_vertex_buffer(std::shared_ptr<VertexBuffer> const& vertex_buffer) = 0;

    /// @brief Get vertex buffers.
    virtual std::vector<std::shared_ptr<VertexBuffer>> const& get_vertex_buffer() const = 0;

    /// @brief Manage a index buffer.
    virtual void set_index_buffer(std::shared_ptr<IndexBuffer> const& index_buffer) = 0;

    /// @brief Get vertex buffers.
    virtual std::shared_ptr<IndexBuffer> const& get_index_buffer() const = 0;

    static std::unique_ptr<VertexArray> create();
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_VERTEX_ARRAY_HPP_
