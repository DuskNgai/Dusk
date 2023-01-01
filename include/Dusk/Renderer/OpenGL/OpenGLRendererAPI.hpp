#ifndef _DUSK_RENDERER_OPENGL_RENDERER_API_HPP_
#define _DUSK_RENDERER_OPENGL_RENDERER_API_HPP_

#include <Dusk/Renderer/RendererAPI.hpp>

DUSK_NAMESPACE_BEGIN

/// @see RendererAPI
class OpenGLRendererAPI : public RendererAPI {
public:
    virtual ~OpenGLRendererAPI() = default;

public:
    virtual void Init() override;
    virtual void Clear() override;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void SetClearColor(glm::vec4 const& color) override;
    virtual void SetLineWidth(float width) override;
    virtual void DrawArrays(VertexArray const* vertex_array) override;
    virtual void DrawElements(VertexArray const* vertex_array, uint32_t count = 0) override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_RENDERER_API_HPP_
