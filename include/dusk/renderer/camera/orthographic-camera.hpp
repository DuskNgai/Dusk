#ifndef _DUSK_RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_HPP_
#define _DUSK_RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_HPP_

#include <dusk/renderer/camera/camera.hpp>

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
    virtual OrthographicCamera* clone() const override;

    virtual void update_from(Camera const* other) override;
    virtual void zoom(float delta) override;

    void set_width(float val);
    float get_width() const;

    virtual glm::vec4 get_clip_position_from_NDC(glm::vec3 const& ndc_coords) const override;

    virtual CameraType get_camera_type() const override;

private:
    virtual glm::mat4 calculate_projection_matrix() const override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_CAMERA_ORTHOGRAPHIC_CAMERA_HPP_
