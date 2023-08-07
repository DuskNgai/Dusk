#include <dusk/scene/camera/camera.hpp>
#include <dusk/scene/camera/orthographic-camera.hpp>
#include <dusk/scene/camera/perspective-camera.hpp>

DUSK_NAMESPACE_BEGIN

Camera::Camera(
    glm::vec3 look_from,
    glm::vec3 look_to,
    glm::vec3 look_up,
    float near_plane,
    float far_plane,
    float aspect_ratio
)
    : m_look_from{ look_from }
    , m_look_to{ look_to }
    , m_look_up{ look_up }
    , m_near_plane{ near_plane }
    , m_far_plane{ far_plane }
    , m_aspect_ratio{ aspect_ratio } {}

std::unique_ptr<Camera> Camera::create(CameraType type) {
    switch (type) {
        case CameraType::Perspective:
            return std::make_unique<PerspectiveCamera>();
        case CameraType::Orthographic:
            return std::make_unique<OrthographicCamera>();
        default:
            return nullptr;
    }
}

void Camera::update_from(Camera const* other) {
    if (this != other) {
        this->m_look_from = other->m_look_from;
        this->m_look_to = other->m_look_to;
        this->m_look_up = other->m_look_up;
        this->m_near_plane = other->m_near_plane;
        this->m_far_plane = other->m_far_plane;
        this->m_aspect_ratio = other->m_aspect_ratio;
        this->invalidate_view_matrix();
        this->invalidate_projection_matrix();
    }
}

void Camera::set_look_from(glm::vec3 const& val) {
    if (this->m_look_from != val) {
        this->m_look_from = val;
        this->invalidate_view_matrix();
    }
}

void Camera::set_look_to(glm::vec3 const& val) {
    if (this->m_look_to != val) {
        this->m_look_to = val;
        this->invalidate_view_matrix();
    }
}

void Camera::set_look_up(glm::vec3 const& val) {
    if (this->m_look_up != val) {
        this->m_look_up = val;
        this->invalidate_view_matrix();
    }
}

void Camera::set_near_plane(float val) {
    if (this->m_near_plane != val) {
        this->m_near_plane = val;
        this->invalidate_projection_matrix();
    }
}

void Camera::set_far_plane(float val) {
    if (this->m_far_plane != val) {
        this->m_far_plane = val;
        this->invalidate_projection_matrix();
    }
}

void Camera::set_aspect_ratio(float val) {
    if (this->m_aspect_ratio != val) {
        this->m_aspect_ratio = val;
        this->invalidate_projection_matrix();
    }
}

glm::vec3 Camera::get_look_from() const { return this->m_look_from; }
glm::vec3 Camera::get_look_to() const { return this->m_look_to; }
glm::vec3 Camera::get_look_up() const { return this->m_look_up; }
float Camera::get_near_plane() const { return this->m_near_plane; }
float Camera::get_far_plane() const { return this->m_far_plane; }
float Camera::get_aspect_ratio() const { return this->m_aspect_ratio; }

glm::mat4 const& Camera::get_view_matrix() const {
    if (this->m_invalid_view_matrix) {
        this->m_view_matrix = this->calculate_view_matrix();
        this->m_inverse_view_matrix = glm::inverse(this->m_view_matrix);
        this->m_invalid_view_matrix = false;
    }
    return this->m_view_matrix;
}

glm::mat4 const& Camera::get_projection_matrix() const {
    if (this->m_invalid_projection_matrix) {
        this->m_projection_matrix = this->calculate_projection_matrix();
        this->m_inverse_projection_matrix = glm::inverse(this->m_projection_matrix);
        this->m_invalid_projection_matrix = false;
    }
    return this->m_projection_matrix;
}

glm::mat4 const& Camera::get_inverse_view_matrix() const {
    if (this->m_invalid_view_matrix) {
        this->get_view_matrix();
    }
    return this->m_inverse_view_matrix;
}

glm::mat4 const& Camera::get_inverse_projection_matrix() const {
    if (this->m_invalid_projection_matrix) {
        this->get_projection_matrix();
    }
    return this->m_inverse_projection_matrix;
}

glm::vec3 Camera::get_world_position_from_NDC(glm::vec3 const& ndc_coords) const {
    auto clip_coords{ this->get_clip_position_from_NDC(ndc_coords) };
    auto eye_coords{ this->get_inverse_projection_matrix() * clip_coords };
    auto world_coords{ this->get_inverse_view_matrix() * eye_coords };
    world_coords /= world_coords.w;
    return { world_coords };
}

glm::vec4 Camera::get_clip_position_from_NDC(glm::vec3 const& ndc_coords) const {
    auto const& projection{ this->get_projection_matrix() };
    float const clip_w{ projection[2][3] / (ndc_coords.z - (projection[2][2] / projection[3][2])) };
    return { ndc_coords * clip_w, clip_w };
}

void Camera::invalidate_view_matrix() { this->m_invalid_view_matrix = true; }
void Camera::invalidate_projection_matrix() { this->m_invalid_projection_matrix = true; }

glm::mat4 Camera::calculate_view_matrix() const {
    return glm::lookAt(
        this->m_look_from, this->m_look_to, this->m_look_up
    );
}

DUSK_NAMESPACE_END
