#ifndef _DUSK_RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_HPP_
#define _DUSK_RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_HPP_

#include <Dusk/Renderer/Camera/Camera.hpp>

DUSK_NAMESPACE_BEGIN

/// @class Orthographic view camera.
/// @see Camera
class OrthographicCamera final : public Camera {
private:
    float m_width;

public:
    OrthographicCamera(
        glm::vec3 look_from = __detail::CAMERA_LOOK_FROM,
        glm::vec3 look_to = __detail::CAMERA_LOOK_TO,
        glm::vec3 look_up = __detail::CAMERA_LOOK_UP,
        float near_plane = __detail::CAMERA_NEAR_PLANE,
        float far_plane = __detail::CAMERA_FAR_PLANE,
        float aspect_ratio = __detail::CAMERA_APECT_RATIO,
        float width = __detail::CAMERA_WIDTH
    );
    virtual ~OrthographicCamera() = default;
    virtual OrthographicCamera* Clone() const override;

    virtual void UpdateFrom(Camera const* other) override;
    virtual void Zoom(float delta) override;

    void SetWidth(float val);
    float GetWidth() const;

    virtual CameraType GetCameraType() const override;

    virtual glm::vec4 GetClipPositionFromNDC(glm::vec3 const& ndc_coords) const override;

private:
    virtual glm::mat4 CalculateProjectionMatrix() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_HPP_
