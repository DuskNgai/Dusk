#ifndef _DUSK_RENDERER_RENDER_COMMAND_HPP_
#define _DUSK_RENDERER_RENDER_COMMAND_HPP_

#include <memory>

#include <Dusk/Renderer/RendererAPI.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The static method class for encapsulating the rendering APIs.
/// Also a singleton class for which a program only needs one renderer.
/// @see RendererAPI
class RenderCommand {
private:
    static std::unique_ptr<RendererAPI> s_render_api;

public:
    static void Init();
    static void Clear();
    static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    static void SetClearColor(glm::vec4 const& color);
    static void SetLineWidth(float width);
    static void DrawArrays(VertexArray const* vertex_array);
    static void DrawElements(VertexArray const* vertex_array, uint32_t count = 0);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_RENDER_COMMAND_HPP_
