#ifndef _DUSK_RENDERER_OPENGL_OPENGL_BUFFER_HPP_
#define _DUSK_RENDERER_OPENGL_OPENGL_BUFFER_HPP_

#include <dusk/renderer/buffer.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief Vertex Buffer using OpenGL APIs.
/// Here we will create a vertex buffer and bind it to the OpenGL context.
class OpenGLVertexBuffer : public VertexBuffer {
private:
    uint32_t m_buffer_id{ 0 };
    BufferLayout m_layout;

public:
    OpenGLVertexBuffer(uint32_t size_in_bytes);
    OpenGLVertexBuffer(uint32_t size_in_bytes, float const* vertices);
    virtual ~OpenGLVertexBuffer() override;

public:
    virtual void bind() const override;
    virtual void unbind() const override;
    virtual void upload(uint32_t size_in_bytes, float const* vertices) override;
    virtual void set_layout(BufferLayout const& layout) override;
    BufferLayout const& get_layout() const override;
};

/// @brief Index Buffer using OpenGL APIs.
/// Here we will create a vertex buffer and bind it to the OpenGL context.
class OpenGLIndexBuffer : public IndexBuffer {
private:
    uint32_t m_buffer_id{ 0 };
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

#endif // !_DUSK_RENDERER_OPENGL_OPENGL_BUFFER_HPP_
