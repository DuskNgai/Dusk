#ifndef _DUSK_RENDERER_OPENGL_BUFFER_HPP_
#define _DUSK_RENDERER_OPENGL_BUFFER_HPP_

#include <dusk/renderer/buffer.hpp>

DUSK_NAMESPACE_BEGIN

/// @class Vertex Buffer using OpenGL APIs.
/// Here we will create a vertex buffer and bind it to the OpenGL context.
/// @see VertexBuffer
class OpenGLVertexBuffer : public VertexBuffer {
private:
    uint32_t m_buffer_id;
    BufferLayout m_layout;

public:
    OpenGLVertexBuffer(uint32_t size_in_bytes);
    OpenGLVertexBuffer(uint32_t size_in_bytes, float const* vertices);
    virtual ~OpenGLVertexBuffer();

public:
    virtual void bind() const override;
    virtual void unbind() const override;
    virtual void set_data(uint32_t size_in_bytes, float const* vertices) override;
    virtual void set_layout(BufferLayout const& layout) override;
    BufferLayout const& get_layout() const override;
};

/// @class Index Buffer using OpenGL APIs.
/// Here we will create a vertex buffer and bind it to the OpenGL context.
/// @see IndexBuffer
class OpenGLIndexBuffer : public IndexBuffer {
private:
    uint32_t m_buffer_id;
    uint32_t m_size;

public:
    OpenGLIndexBuffer(uint32_t size_in_bytes, uint32_t const* indices);
    virtual ~OpenGLIndexBuffer();

public:
    virtual void bind() const override;
    virtual void unbind() const override;
    virtual uint32_t size() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_BUFFER_HPP_
