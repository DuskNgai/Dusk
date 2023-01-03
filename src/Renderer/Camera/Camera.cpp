#include <Dusk/Renderer/Camera/Camera.hpp>
#include <Dusk/Renderer/Camera/OrthographicCamera.hpp>
#include <Dusk/Renderer/Camera/PerspectiveCamera.hpp>

DUSK_NAMESPACE_BEGIN

Camera::Camera(
    glm::vec3 look_from, glm::vec3 look_to, glm::vec3 look_up,
    float near_plane, float far_plane, float aspect_ratio
)
    : m_look_from(look_from)
    , m_look_to(look_to)
    , m_look_up(look_up)
    , m_near_plane(near_plane)
    , m_far_plane(far_plane)
    , m_aspect_ratio(aspect_ratio) {}

std::unique_ptr<Camera> Camera::Create(CameraType type) {
    switch (type) {
        case CameraType::Perspective:
            return std::make_unique<PerspectiveCamera>();
        case CameraType::Orthographic:
            return std::make_unique<OrthographicCamera>();
    }
}

void Camera::UpdateFrom(Camera const* other) {
    if (this != other) {
        this->m_look_from = other->m_look_from;
        this->m_look_to = other->m_look_to;
        this->m_look_up = other->m_look_up;
        this->m_near_plane = other->m_near_plane;
        this->m_far_plane = other->m_far_plane;
        this->m_aspect_ratio = other->m_aspect_ratio;
        this->InvalidateViewMatrix();
        this->InvalidateProjectionMatrix();
    }
}

void Camera::SetLookFrom(glm::vec3 val) {
    if (this->m_look_from != val) {
        this->m_look_from = val;
        this->InvalidateViewMatrix();
    }
}

void Camera::SetLookTo(glm::vec3 val) {
    if (this->m_look_to != val) {
        this->m_look_to = val;
        this->InvalidateViewMatrix();
    }
}

void Camera::SetLookUp(glm::vec3 val) {
    if (this->m_look_up != val) {
        this->m_look_up = val;
        this->InvalidateViewMatrix();
    }
}

void Camera::SetNearPlane(float val) {
    if (this->m_near_plane != val) {
        this->m_near_plane = val;
        this->InvalidateProjectionMatrix();
    }
}

void Camera::SetFarPlane(float val) {
    if (this->m_far_plane != val) {
        this->m_far_plane = val;
        this->InvalidateProjectionMatrix();
    }
}

void Camera::SetAspectRatio(float val) {
    if (this->m_aspect_ratio != val) {
        this->m_aspect_ratio = val;
        this->InvalidateProjectionMatrix();
    }
}

glm::vec3 Camera::GetLookFrom() const { return this->m_look_from; }
glm::vec3 Camera::GetLookTo() const { return this->m_look_to; }
glm::vec3 Camera::GetLookUp() const { return this->m_look_up; }
float Camera::GetNearPlane() const { return this->m_near_plane; }
float Camera::GetFarPlane() const { return this->m_far_plane; }
float Camera::GetAspectRatio() const { return this->m_aspect_ratio; }

glm::mat4 const& Camera::GetViewMatrix() const {
    if (this->m_invalid_view_matrix) {
        this->m_view_matrix = this->CalculateViewMatrix();
        this->m_inverse_view_matrix = glm::inverse(this->m_view_matrix);
        this->m_invalid_view_matrix = false;
    }
    return this->m_view_matrix;
}

glm::mat4 const& Camera::GetProjectionMatrix() const {
    if (this->m_invalid_projection_matrix) {
        this->m_projection_matrix = this->CalculateProjectionMatrix();
        this->m_inverse_projection_matrix = glm::inverse(this->m_projection_matrix);
        this->m_invalid_projection_matrix = false;
    }
    return this->m_projection_matrix;
}

glm::mat4 const& Camera::GetInverseViewMatrix() const {
    if (this->m_invalid_view_matrix) {
        this->GetViewMatrix();
    }
    return this->m_inverse_view_matrix;
}

glm::mat4 const& Camera::GetInverseProjectionMatrix() const {
    if (this->m_invalid_projection_matrix) {
        this->GetProjectionMatrix();
    }
    return this->m_inverse_projection_matrix;
}

glm::vec3 Camera::GetWorldPositionFromNDC(glm::vec3 const& ndc_coords) const {
    auto clip_coords = this->GetClipPositionFromNDC(ndc_coords);
    auto eye_coords = this->GetInverseProjectionMatrix() * clip_coords;
    auto world_coords = this->GetInverseViewMatrix() * eye_coords;
    world_coords /= world_coords.w;
    return glm::vec3{world_coords};
}

glm::vec4 Camera::GetClipPositionFromNDC(glm::vec3 const& ndc_coords) const {
    auto const& projection = this->GetProjectionMatrix();
    float const clip_w = projection[2][3] / (ndc_coords.z - (projection[2][2] / projection[3][2]));
    return glm::vec4{ndc_coords * clip_w, clip_w};
}

void Camera::InvalidateViewMatrix() { this->m_invalid_view_matrix = true; }
void Camera::InvalidateProjectionMatrix() { this->m_invalid_projection_matrix = true; }

glm::mat4 Camera::CalculateViewMatrix() const {
    return glm::lookAt(
        this->m_look_from, this->m_look_to, this->m_look_up
    );
}

DUSK_NAMESPACE_END
