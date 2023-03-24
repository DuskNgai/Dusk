#ifndef _DUSK_RENDERER_RENDER_COMMAND_HPP_
#define _DUSK_RENDERER_RENDER_COMMAND_HPP_

#include <memory>

#include <dusk/renderer/renderer-API.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The static method class for encapsulating the rendering APIs.
/// Also a singleton class for which a program only needs one renderer.
/// @see RendererAPI
class RenderCommand {
private:
    static std::unique_ptr<RendererAPI> s_render_api;

public:
    static void init();
    static void clear();
    static void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    static void set_clear_color(glm::vec4 const& color);
    static void set_line_width(float width);
    static void draw_arrays(VertexArray const* vertex_array);
    static void draw_elements(VertexArray const* vertex_array, uint32_t count = 0);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_RENDER_COMMAND_HPP_
