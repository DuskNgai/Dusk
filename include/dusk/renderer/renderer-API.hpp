#ifndef _DUSK_RENDERER_RENDERER_API_HPP_
#define _DUSK_RENDERER_RENDERER_API_HPP_

#include <glm/glm.hpp>

#include <dusk/renderer/vertex-array.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The runtime graphics APIs.
/// Usually this singleton class will not be called directly,
/// we will use static methods in `RenderCommand` instead.
class RendererAPI {
public:
    /// @brief These are the rendering APIs we might use.
    enum class API {
        None = 0,
        OpenGL,
        Vulkan,
        DirectX12
    };

private:
    /// @brief The rendering API we are using.
    static API s_API;

public:
    virtual ~RendererAPI() = default;

public:
    virtual void init() = 0;

    virtual void clear() = 0;

    virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

    virtual void set_clear_color(glm::vec4 const& color) = 0;

    virtual void set_line_width(float width) = 0;

    virtual void draw_arrays(VertexArray const* vertex_array) = 0;

    /// @brief Draw data in `vertex_array` with index buffer.
    /// If `count` is 0, then the index buffer stored inside the vertex array will be used.
    /// If `count` is not 0, then it will draw `count / 6` triangles.
    virtual void draw_elements(VertexArray const* vertex_array, uint32_t count = 0) = 0;

    static API get_API();

    static std::unique_ptr<RendererAPI> create();
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_RENDERER_API_HPP_
