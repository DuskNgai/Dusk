#ifndef _DUSK_RENDERER_OPENGL_OPENGL_RENDERER_API_HPP_
#define _DUSK_RENDERER_OPENGL_OPENGL_RENDERER_API_HPP_

#include <dusk/renderer/renderer-API.hpp>

DUSK_NAMESPACE_BEGIN

/// @see RendererAPI
class OpenGLRendererAPI : public RendererAPI {
public:
    virtual ~OpenGLRendererAPI() = default;

public:
    virtual void initialize() override;
    virtual void clear() override;
    virtual void enable_render_test(RenderTest test) override;
    virtual void disable_render_test(RenderTest test) override;
    virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void set_clear_color(glm::vec4 const& color) override;
    virtual void set_line_width(float width) override;
    virtual void draw_arrays(VertexArray const* vertex_array) override;
    virtual void draw_elements(VertexArray const* vertex_array, uint32_t count = 0) override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_OPENGL_RENDERER_API_HPP_
