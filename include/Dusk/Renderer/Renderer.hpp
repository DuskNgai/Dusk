#ifndef _DUSK_RENDERER_RENDERER_HPP_
#define _DUSK_RENDERER_RENDERER_HPP_

#include <memory>

#include <Dusk/Renderer/Camera/Camera.hpp>
#include <Dusk/Renderer/RenderCommand.hpp>
#include <Dusk/Renderer/Shader.hpp>
#include <Dusk/Renderer/VertexArray.hpp>

DUSK_NAMESPACE_BEGIN

/// @class An abstract class which defines the interface for rendering.
/// It is independent of the rendering APIs.
class Renderer {
private:
    struct RenderData {
        Camera* camera;
    };
    static std::unique_ptr<RenderData> s_render_data;

public:
    /// @brief Initialize all the rendering APIs settings related to this renderer.
    static void Init();

    /// @brief Shut down all the rendering APIs settings related to this renderer.
    static void Shutdown();

    /// @brief Register objects (cameras, materials, geometries, etc) in scene.
    static void BeginScene(Camera* camera);

    /// @brief End of creating the scene, do nothing at all.
    static void EndScene();

    /// @brief Submit graphics primitives to render.
    static void Submit(
        Shader const* shader,
        VertexArray const* vertex_array,
        glm::mat4 const& model = glm::mat4(1.0f)
    );
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_RENDERER_HPP_
