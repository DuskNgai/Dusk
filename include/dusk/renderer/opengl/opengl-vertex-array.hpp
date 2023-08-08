#ifndef _DUSK_RENDERER_OPENGL_OPENGL_VERTEX_ARRAY_HPP_
#define _DUSK_RENDERER_OPENGL_OPENGL_VERTEX_ARRAY_HPP_

#include <memory>
#include <vector>
#include <type_traits>

#include <dusk/renderer/vertex-array.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief Vertex array using OpenGL APIs.
/// @see VertexArray
class OpenGLVertexArray : public VertexArray {
private:
    uint32_t m_array_id;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
    std::shared_ptr<IndexBuffer> m_index_buffer;

public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray() override;

public:
    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void add_vertex_buffer(std::shared_ptr<VertexBuffer> const& vertex_buffer) override;
    virtual std::vector<std::shared_ptr<VertexBuffer>> const& get_vertex_buffer() const override;
    virtual void set_index_buffer(std::shared_ptr<IndexBuffer> const& index_buffer) override;
    virtual std::shared_ptr<IndexBuffer> const& get_index_buffer() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_OPENGL_VERTEX_ARRAY_HPP_
