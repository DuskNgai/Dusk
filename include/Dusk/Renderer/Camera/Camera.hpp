#ifndef _DUSK_RENDERER_CAMERA_CAMERA_HPP_
#define _DUSK_RENDERER_CAMERA_CAMERA_HPP_

#include <memory>

#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include <Dusk/Common.hpp>
#include <Dusk/PlatformDetection.hpp>

DUSK_NAMESPACE_BEGIN

namespace __detail {
#if defined(DUSK_PLATFORM_WINDOWS)
    // Avoid weird bug cooperates with nvcc on Windows.
    const glm::vec3 CAMERA_LOOK_FROM{0.0f, 0.0f, 5.0f};
    const glm::vec3 CAMERA_LOOK_TO{0.0f, 0.0f, 0.0f};
    const glm::vec3 CAMERA_LOOK_UP{0.0f, 1.0f, 0.0f};
#elif defined(DUSK_PLATFORM_LINUX)
    constexpr glm::vec3 CAMERA_LOOK_FROM{0.0f, 0.0f, 5.0f};
    constexpr glm::vec3 CAMERA_LOOK_TO{0.0f, 0.0f, 0.0f};
    constexpr glm::vec3 CAMERA_LOOK_UP{0.0f, 1.0f, 0.0f};
#endif
    constexpr float CAMERA_NEAR_PLANE{0.1f};
    constexpr float CAMERA_FAR_PLANE{100.0f};
    constexpr float CAMERA_APECT_RATIO{16.0f / 9.0f};
    constexpr float CAMERA_FIELD_OF_VIEW{30.0f};
    constexpr float CAMERA_WIDTH{3.2f};
} // namespace __detail

/// @see OrthographicCamera, PerspectiveCamera
enum class CameraType {
    Orthographic,
    Perspective,
};

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
    mutable glm::mat4 m_view_matrix{glm::mat4{1.0f}};
    mutable glm::mat4 m_inverse_view_matrix{glm::mat4{1.0f}};
    mutable glm::mat4 m_projection_matrix{glm::mat4{1.0f}};
    mutable glm::mat4 m_inverse_projection_matrix{glm::mat4{1.0f}};
    mutable bool m_invalid_view_matrix{true};
    mutable bool m_invalid_projection_matrix{true};

public:
    Camera(
        glm::vec3 look_from, glm::vec3 look_to, glm::vec3 look_up,
        float near_plane, float far_plane, float aspect_ratio
    );
    virtual ~Camera() = default;
    virtual Camera* Clone() const = 0;
    static std::unique_ptr<Camera> Create(CameraType type);

public:
    virtual void UpdateFrom(Camera const* other);
    virtual void Zoom(float delta) = 0;

    void SetLookFrom(glm::vec3 val);
    void SetLookTo(glm::vec3 val);
    void SetLookUp(glm::vec3 val);
    void SetNearPlane(float val);
    void SetFarPlane(float val);
    void SetAspectRatio(float val);

    glm::vec3 GetLookFrom() const;
    glm::vec3 GetLookTo() const;
    glm::vec3 GetLookUp() const;
    float GetNearPlane() const;
    float GetFarPlane() const;
    float GetAspectRatio() const;

    virtual CameraType GetCameraType() const = 0;

    glm::mat4 const& GetViewMatrix() const;
    glm::mat4 const& GetProjectionMatrix() const;
    glm::mat4 const& GetInverseViewMatrix() const;
    glm::mat4 const& GetInverseProjectionMatrix() const;

    /// @brief Convert from normalized device coordinates (NDC: where x,y,z in [-1, 1]) to world coordinates.
    glm::vec3 GetWorldPositionFromNDC(glm::vec3 const& ndc_coords) const;

    /// @brief Convert from normalized device coordinates (NDC: where x,y,z in [-1, 1]) to clip coordinates.
    /// where z value of -1 correspond to the near plane and 1 to the far plane.
    /// Coordinates outside of the [-1 1]^3 range will be clipped.
    virtual glm::vec4 GetClipPositionFromNDC(glm::vec3 const& ndc_coords) const;

protected:
    /// @brief When set one component of camera, we do lazy change.
    /// So here we just mark the old matrix invalid.
    void InvalidateViewMatrix();
    void InvalidateProjectionMatrix();

    /// @brief Calculate the matrix if they are valid.
    virtual glm::mat4 CalculateViewMatrix() const;
    virtual glm::mat4 CalculateProjectionMatrix() const = 0;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_CAMERA_CAMERA_HPP_
