#ifndef _DUSK_RENDERER_CAMERA_CAMERA_HPP_
#define _DUSK_RENDERER_CAMERA_CAMERA_HPP_

#include <memory>

#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include <dusk/common.hpp>
#include <dusk/platform-detection.hpp>
#include <dusk/renderer/camera/camera-utils.hpp>

DUSK_NAMESPACE_BEGIN

namespace __detail {
#if defined(DUSK_PLATFORM_WINDOWS) && defined(__NVCC__)
    // Avoid weird bug cooperates with nvcc on Windows.
    const glm::vec3 CAMERA_LOOK_FROM{ 0.0f, 0.0f, 5.0f };
    const glm::vec3 CAMERA_LOOK_TO{ 0.0f, 0.0f, 0.0f };
    const glm::vec3 CAMERA_LOOK_UP{ 0.0f, 1.0f, 0.0f };
#else
    constexpr glm::vec3 CAMERA_LOOK_FROM{ 0.0f, 0.0f, 5.0f };
    constexpr glm::vec3 CAMERA_LOOK_TO{ 0.0f, 0.0f, 0.0f };
    constexpr glm::vec3 CAMERA_LOOK_UP{ 0.0f, 1.0f, 0.0f };
#endif
    constexpr float CAMERA_NEAR_PLANE{ 0.1f };
    constexpr float CAMERA_FAR_PLANE{ 100.0f };
    constexpr float CAMERA_APECT_RATIO{ 16.0f / 9.0f };
    constexpr float CAMERA_FIELD_OF_VIEW{ 60.0f };
    constexpr float CAMERA_WIDTH{ 3.2f };
} // namespace __detail

/// @class The base class for FPS-like cameras.
/// @see OrthographicCamera, PerspectiveCamera
class Camera {
protected:
    glm::vec3 m_look_from;
    glm::vec3 m_look_to;
    glm::vec3 m_look_up;

    float m_near_plane;
    float m_far_plane;
    float m_aspect_ratio;

    // Make mutable to allow to be changed even called by const function.

    mutable glm::mat4 m_view_matrix{ glm::mat4{ 1.0f } };
    mutable glm::mat4 m_inverse_view_matrix{ glm::mat4{ 1.0f } };
    mutable glm::mat4 m_projection_matrix{ glm::mat4{ 1.0f } };
    mutable glm::mat4 m_inverse_projection_matrix{ glm::mat4{ 1.0f } };
    mutable bool m_invalid_view_matrix{ true };
    mutable bool m_invalid_projection_matrix{ true };

public:
    Camera(
        glm::vec3 look_from, glm::vec3 look_to, glm::vec3 look_up,
        float near_plane, float far_plane, float aspect_ratio
    );
    virtual ~Camera() = default;
    virtual Camera* clone() const = 0;
    static std::unique_ptr<Camera> create(CameraType type);

public:
    virtual void update_from(Camera const* other);
    virtual void zoom(float delta) = 0;

    void set_look_from(glm::vec3 const& val);
    void set_look_to(glm::vec3 const& val);
    void set_look_up(glm::vec3 const& val);
    void set_near_plane(float val);
    void set_far_plane(float val);
    void set_aspect_ratio(float val);

    glm::vec3 get_look_from() const;
    glm::vec3 get_look_to() const;
    glm::vec3 get_look_up() const;
    float get_near_plane() const;
    float get_far_plane() const;
    float get_aspect_ratio() const;

    virtual CameraType get_camera_type() const = 0;

    glm::mat4 const& get_view_matrix() const;
    glm::mat4 const& get_projection_matrix() const;
    glm::mat4 const& get_inverse_view_matrix() const;
    glm::mat4 const& get_inverse_projection_matrix() const;

    /// @brief Convert from normalized device coordinates (NDC: where x,y,z in [-1, 1]) to world coordinates.
    glm::vec3 get_world_position_from_NDC(glm::vec3 const& ndc_coords) const;

    /// @brief Convert from normalized device coordinates (NDC: where x,y,z in [-1, 1]) to clip coordinates.
    /// where z value of -1 correspond to the near plane and 1 to the far plane.
    /// Coordinates outside of the [-1 1]^3 range will be clipped.
    virtual glm::vec4 get_clip_position_from_NDC(glm::vec3 const& ndc_coords) const;

protected:
    /// @brief When set one component of camera, we do lazy change.
    /// So here we just mark the old matrix invalid.
    void invalidate_view_matrix();
    void invalidate_projection_matrix();

    /// @brief Calculate the matrix if they are invalid.
    virtual glm::mat4 calculate_view_matrix() const;
    virtual glm::mat4 calculate_projection_matrix() const = 0;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_CAMERA_CAMERA_HPP_
