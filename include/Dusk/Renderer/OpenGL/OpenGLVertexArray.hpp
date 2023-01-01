#ifndef _DUSK_RENDERER_OPENGL_VERTEX_ARRAY_HPP_
#define _DUSK_RENDERER_OPENGL_VERTEX_ARRAY_HPP_

#include <memory>
#include <vector>

#include <Dusk/Renderer/VertexArray.hpp>

DUSK_NAMESPACE_BEGIN

/// @class Vertex array using OpenGL APIs.
/// @see VertexArray
class OpenGLVertexArray : public VertexArray {
private:
    uint32_t m_array_id;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
    std::shared_ptr<IndexBuffer> m_index_buffer;

public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

public:
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> const& vertex_buffer) override;
    virtual std::vector<std::shared_ptr<VertexBuffer>> const& GetVertexBuffers() const override;
    virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> const& index_buffer) override;
    virtual std::shared_ptr<IndexBuffer> const& GetIndexBuffer() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_VERTEX_ARRAY_HPP_
