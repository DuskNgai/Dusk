#ifndef _DUSK_RENDERER_RENDERER_API_HPP_
#define _DUSK_RENDERER_RENDERER_API_HPP_

#include <glm/glm.hpp>

#include <Dusk/Renderer/VertexArray.hpp>

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
    /// @brief Get the current rendering API.
    static API GetAPI();

    static std::unique_ptr<RendererAPI> Create();

    /// @brief Initialize all the rendering APIs related to this renderer.
    virtual void Init() = 0;

    /// @brief Clear the window
    virtual void Clear() = 0;

    /// @brief Set the new viewport especially when the window gets resized.
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

    /// @brief Set the window clear color.
    virtual void SetClearColor(glm::vec4 const& color) = 0;

    /// @brief Set the line strip width in window.
    virtual void SetLineWidth(float width) = 0;

    /// @brief Draw data in `vertex_array` without index buffer.
    virtual void DrawArrays(VertexArray const* vertex_array) = 0;

    /// @brief Draw data in `vertex_array` with index buffer.
    /// If `count` is 0, then the index buffer stored inside the vertex array will be used.
    /// If `count` is not 0, then it will draw `count / 6` triangles.
    virtual void DrawElements(VertexArray const* vertex_array, uint32_t count = 0) = 0;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_RENDERER_API_HPP_
