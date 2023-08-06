#ifndef _DUSK_RENDERER_RENDERER_2D_HPP_
#define _DUSK_RENDERER_RENDERER_2D_HPP_

#include <array>
#include <memory>

#include <dusk/scene/camera/camera.hpp>
#include <dusk/renderer/vertex-array.hpp>
#include <dusk/renderer/buffer.hpp>
#include <dusk/renderer/shader.hpp>
#include <dusk/renderer/texture.hpp>
#include <dusk/platform-detection.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief The default settings for Renderer2D;
namespace __detail {
    constexpr float RENDERER2D_TILING_SCALE{ 1.0f };  // For pure color + white texture.
    constexpr float RENDERER2D_TEXTURE_INDEX{ 0.0f }; // For pure color + white texture.

#if defined(DUSK_PLATFORM_WINDOWS) && defined(__NVCC__)
    // Avoid weird bug cooperates with nvcc on Windows.
    const glm::vec4 RENDERER2D_COLOR{ 1.0f, 1.0f, 1.0f, 1.0f };      // For texture.

    const std::array<glm::vec4, 4> RENDERER2D_VERTICES{
        glm::vec4{-0.5f, -0.5f, 0.0f, 1.0f},
        glm::vec4{ 0.5f, -0.5f, 0.0f, 1.0f},
        glm::vec4{ 0.5f,  0.5f, 0.0f, 1.0f},
        glm::vec4{-0.5f,  0.5f, 0.0f, 1.0f},
    };
    const std::array<glm::vec2, 4> RENDERER2D_UVS{
        glm::vec2{0.0f, 0.0f},
        glm::vec2{1.0f, 0.0f},
        glm::vec2{1.0f, 1.0f},
        glm::vec2{0.0f, 1.0f},
    };
#else
    constexpr glm::vec4 RENDERER2D_COLOR{ 1.0f, 1.0f, 1.0f, 1.0f };      // For texture.

    constexpr std::array<glm::vec4, 4> RENDERER2D_VERTICES{
        glm::vec4{-0.5f, -0.5f, 0.0f, 1.0f},
        glm::vec4{ 0.5f, -0.5f, 0.0f, 1.0f},
        glm::vec4{ 0.5f,  0.5f, 0.0f, 1.0f},
        glm::vec4{-0.5f,  0.5f, 0.0f, 1.0f},
    };
    constexpr std::array<glm::vec2, 4> RENDERER2D_UVS{
        glm::vec2{0.0f, 0.0f},
        glm::vec2{1.0f, 0.0f},
        glm::vec2{1.0f, 1.0f},
        glm::vec2{0.0f, 1.0f},
    };
#endif
    constexpr uint32_t RENDERER2D_QUADS_BUFFER_SIZE{ 1 << 14 };
    constexpr uint32_t RENDERER2D_QUADS_VERTICES_COUNT{ 4 }; // 4 RENDERER2D_VERTICES per quad.
    constexpr uint32_t RENDERER2D_VERTICES_BUFFER_SIZE{ RENDERER2D_QUADS_BUFFER_SIZE * RENDERER2D_QUADS_VERTICES_COUNT };
    constexpr uint32_t RENDERER2D_INDICES_BUFFER_SIZE{ RENDERER2D_QUADS_BUFFER_SIZE * 6 }; // 6 indices per quad.

    constexpr uint32_t RENDERER2D_TEXTURE_SLOTS_SIZE{ 32 }; // May be different at different platform.
} // namespace __detail

/// @class A 2D basic primitives rendering library.
/// Currently supported primitives:
/// Quad
class Renderer2D {
private:
    /// @brief Data for vertex.
    struct QuadVertex {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 tex_coord;
        float tex_index;
        float tiling_scale;
    };

    /// @brief Data structures for Renderer2D.
    struct Renderer2DData {
        std::vector<QuadVertex> quad_vertex_buffer_cpu;
        std::vector<uint32_t> quad_index_buffer_cpu;
        std::vector<std::shared_ptr<Texture>> texture_slots_cpu;

        std::unique_ptr<VertexArray> quad_vertex_array;
        std::shared_ptr<VertexBuffer> quad_vertex_buffer;
        std::shared_ptr<Shader> texture_shader;
        std::shared_ptr<Texture2D> white_texture;
    };
    static std::unique_ptr<Renderer2DData> s_data;

public:
    static void init();

    static void shut_down();

    /// @brief Register objects (cameras, materials, geometries, etc) in scene.
    static void begin_scene(Camera* camera);

    /// @brief End of creating the scene, do nothing at all.
    static void end_scene();

    /// @brief Flush the actual vertex data buffer if scene is end or buffer is full.
    static void flush();

public:
    /// @brief Draw a quad/square.
    /// @param position The center of the quad.
    /// @param size The size of the quad for each axis.
    /// @param color The color of the quad.
    /// @param texture The texture of the quad.
    static void draw_quad(glm::vec2 const& position, glm::vec2 const& size, glm::vec4 const& color);
    static void draw_quad(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color);
    static void draw_quad(glm::vec2 const& position, glm::vec2 const& size, std::shared_ptr<Texture> const& texture, float tiling_scale = 1.0f);
    static void draw_quad(glm::vec3 const& position, glm::vec2 const& size, std::shared_ptr<Texture> const& texture, float tiling_scale = 1.0f);

    /// @brief Draw a rotated quad/square with rotation axis z.
    /// @param position The center of the quad.
    /// @param size The size of the quad for each axis.
    /// @param radians The rotation of the quad, must be in radians.
    /// @param color The color of the quad.
    /// @param texture The texture of the quad, 0 for pure white texture.
    static void draw_rotated_quad(glm::vec2 const& position, glm::vec2 const& size, float radians, glm::vec4 const& color);
    static void draw_rotated_quad(glm::vec3 const& position, glm::vec2 const& size, float radians, glm::vec4 const& color);
    static void draw_rotated_quad(glm::vec2 const& position, glm::vec2 const& size, float radians, std::shared_ptr<Texture> const& texture, float tiling_scale = 1.0f);
    static void draw_rotated_quad(glm::vec3 const& position, glm::vec2 const& size, float radians, std::shared_ptr<Texture> const& texture, float tiling_scale = 1.0f);

    /// @brief Final `draw_quad` dispatched function for pure color.
    static void draw_quad(glm::mat4 const& model, glm::vec4 const& color);
    /// @brief Final `draw_quad` dispatched function for texture.
    static void draw_quad(glm::mat4 const& model, std::shared_ptr<Texture> const& texture, float tiling_scale = 1.0f);

private:
    /// @brief Clear the CPU buffer.
    static void start_batch();

    /// @brief Upload and draw the data stored in the CPU buffer (flush)
    /// and clear them (start_batch).
    static void next_batch();
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_RENDERER_2D_HPP_
