#ifndef _DUSK_RENDERER_OPENGL_BUFFER_HPP_
#define _DUSK_RENDERER_OPENGL_BUFFER_HPP_

#include <Dusk/Renderer/Buffer.hpp>

DUSK_NAMESPACE_BEGIN

/// @class Vertex Buffer using OpenGL APIs.
/// Here we will create a vertex buffer and bind it to the OpenGL context.
/// @see VertexBuffer
class OpenGLVertexBuffer : public VertexBuffer {
private:
    uint32_t m_buffer_id;
    BufferLayout m_layout;

public:
    OpenGLVertexBuffer(uint32_t size);
    OpenGLVertexBuffer(uint32_t size, float* vertices);
    ~OpenGLVertexBuffer();

public:
    void Bind() const override;
    void Unbind() const override;
    void SetData(uint32_t size, float* vertices) override;
    void SetLayout(BufferLayout const& layout) override;
    BufferLayout const& GetLayout() const override;
};

/// @class Index Buffer using OpenGL APIs.
/// Here we will create a vertex buffer and bind it to the OpenGL context.
/// @see IndexBuffer
class OpenGLIndexBuffer : public IndexBuffer {
private:
    uint32_t m_buffer_id;
    uint32_t m_size;

public:
    OpenGLIndexBuffer(uint32_t size, uint32_t* indices);
    ~OpenGLIndexBuffer();

public:
    void Bind() const override;
    void Unbind() const override;
    uint32_t Size() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_BUFFER_HPP_
