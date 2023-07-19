#ifndef _DUSK_RENDERER_RENDERER_HPP_
#define _DUSK_RENDERER_RENDERER_HPP_

#include <memory>

#include <dusk/scene/camera/camera.hpp>
#include <dusk/renderer/render-command.hpp>
#include <dusk/renderer/shader.hpp>
#include <dusk/renderer/vertex-array.hpp>

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
    static void init();

    static void shut_down();

    /// @brief Register objects (cameras, materials, geometries, etc) in scene.
    static void begin_scene(Camera* camera);

    /// @brief End of creating the scene, do nothing at all.
    static void end_scene();

    /// @brief Submit graphics primitives to render.
    static void submit(
        std::shared_ptr<Shader> const& shader,
        std::unique_ptr<VertexArray> const& vertex_array,
        glm::mat4 const& model = glm::mat4(1.0f)
    );
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_RENDERER_HPP_
