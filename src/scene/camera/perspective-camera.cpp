#include <dusk/scene/camera/camera-utils.hpp>
#include <dusk/scene/camera/orthographic-camera.hpp>
#include <dusk/scene/camera/perspective-camera.hpp>

DUSK_NAMESPACE_BEGIN

PerspectiveCamera::PerspectiveCamera(
    glm::vec3 look_from, glm::vec3 look_to, glm::vec3 look_up,
    float near_plane, float far_plane, float aspect_ratio,
    float field_of_view
)
    : Camera{ look_from, look_to, look_up, near_plane, far_plane, aspect_ratio }
    , m_field_of_view{ field_of_view } {}

PerspectiveCamera* PerspectiveCamera::clone() const {
    return new PerspectiveCamera(*this);
}

void PerspectiveCamera::update_from(Camera const* other) {
    Camera::update_from(other);
    if (auto pc{ dynamic_cast<PerspectiveCamera const*>(other) }) {
        this->set_field_of_view(pc->get_field_of_view());
    }
    else if (auto oc{ dynamic_cast<OrthographicCamera const*>(other) }) {
        this->set_field_of_view(width_to_yfov(oc->get_width(), glm::distance(this->get_look_from(), this->get_look_to()), this->get_aspect_ratio()));
    }
}

void PerspectiveCamera::zoom(float delta) {
    auto fov{ std::max(0.1f, std::min(this->get_field_of_view() + delta, 100.0f)) };
    this->set_field_of_view(fov);
}

void PerspectiveCamera::set_field_of_view(float degrees) {
    if (this->m_field_of_view != degrees) {
        this->m_field_of_view = degrees;
        this->invalidate_projection_matrix();
    }
}

float PerspectiveCamera::get_field_of_view() const { return this->m_field_of_view; }

CameraType PerspectiveCamera::get_camera_type() const { return CameraType::Perspective; }

glm::mat4 PerspectiveCamera::calculate_projection_matrix() const {
    return glm::perspective(
        glm::radians(this->m_field_of_view), this->m_aspect_ratio, this->m_near_plane, this->m_far_plane
    );
}

DUSK_NAMESPACE_END
