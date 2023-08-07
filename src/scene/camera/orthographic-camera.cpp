#include <dusk/scene/camera/camera-utils.hpp>
#include <dusk/scene/camera/orthographic-camera.hpp>
#include <dusk/scene/camera/perspective-camera.hpp>

DUSK_NAMESPACE_BEGIN

OrthographicCamera::OrthographicCamera(
    glm::vec3 look_from,
    glm::vec3 look_to,
    glm::vec3 look_up,
    float near_plane,
    float far_plane,
    float aspect_ratio,
    float width
)
    : Camera{ look_from, look_to, look_up, near_plane, far_plane, aspect_ratio }
    , m_width{ width } {}

OrthographicCamera* OrthographicCamera::clone() const {
    return new OrthographicCamera(*this);
}

void OrthographicCamera::update_from(Camera const* other) {
    Camera::update_from(other);
    if (auto oc{ dynamic_cast<OrthographicCamera const*>(other) }) {
        this->set_width(oc->get_width());
    }
    else if (auto pc{ dynamic_cast<PerspectiveCamera const*>(other) }) {
        this->set_width(yfov_to_width(pc->get_field_of_view(), glm::distance(this->get_look_from(), this->get_look_to()), this->get_aspect_ratio()));
    }
}

void OrthographicCamera::zoom(float delta) {
    auto width{ std::max(0.1f, std::min(this->get_width() + delta, 100.0f)) };
    this->set_width(width);
}

void OrthographicCamera::set_width(float val) {
    if (this->m_width != val) {
        this->m_width = val;
        this->invalidate_projection_matrix();
    }
}

float OrthographicCamera::get_width() const { return this->m_width; }

CameraType OrthographicCamera::get_camera_type() const { return CameraType::Orthographic; }

glm::vec4 OrthographicCamera::get_clip_position_from_NDC(glm::vec3 const& ndc_coords) const {
    return { ndc_coords, 1.0f };
}

glm::mat4 OrthographicCamera::calculate_projection_matrix() const {
    auto half_width{ this->m_width * 0.5f };
    auto half_height{ half_width / this->m_aspect_ratio };
    return glm::ortho(
        -half_width, half_width, -half_height, half_height, this->m_near_plane, this->m_far_plane
    );
}

DUSK_NAMESPACE_END
