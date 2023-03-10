#ifndef _DUSK_RENDERER_CAMERA_PERSPECTIVE_CAMERA_HPP_
#define _DUSK_RENDERER_CAMERA_PERSPECTIVE_CAMERA_HPP_

#include <Dusk/Renderer/Camera/Camera.hpp>

DUSK_NAMESPACE_BEGIN

/// @class Perspective view camera.
/// @see Camera
class PerspectiveCamera final : public Camera {
private:
    // Fov in y direction, in degrees.
    float m_field_of_view;

public:
    PerspectiveCamera(
        glm::vec3 look_from = __detail::CAMERA_LOOK_FROM,
        glm::vec3 look_to = __detail::CAMERA_LOOK_TO,
        glm::vec3 look_up = __detail::CAMERA_LOOK_UP,
        float near_plane = __detail::CAMERA_NEAR_PLANE,
        float far_plane = __detail::CAMERA_FAR_PLANE,
        float aspect_ratio = __detail::CAMERA_APECT_RATIO,
        float field_of_view = __detail::CAMERA_FIELD_OF_VIEW
    );
    virtual ~PerspectiveCamera() = default;
    virtual PerspectiveCamera* Clone() const override;

    virtual void UpdateFrom(Camera const* other) override;
    virtual void Zoom(float delta) override;

    void SetFieldOfView(float degrees);
    float GetFieldOfView() const;

    virtual CameraType GetCameraType() const override;

private:
    virtual glm::mat4 CalculateProjectionMatrix() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_CAMERA_PERSPECTIVE_CAMERA_HPP_
