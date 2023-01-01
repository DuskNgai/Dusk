#include <Dusk/Renderer/Camera/PerspectiveCamera.hpp>

DUSK_NAMESPACE_BEGIN

PerspectiveCamera::PerspectiveCamera(
    glm::vec3 look_from, glm::vec3 look_to, glm::vec3 look_up,
    float near_plane, float far_plane, float aspect_ratio,
    float field_of_view
)
    : Camera(look_from, look_to, look_up, near_plane, far_plane, aspect_ratio)
    , m_field_of_view(field_of_view) {}

PerspectiveCamera* PerspectiveCamera::clone() const {
    return new PerspectiveCamera(*this);
}

void PerspectiveCamera::SetFieldOfView(float val) {
    if (this->m_field_of_view != val) {
        this->m_field_of_view = val;
        this->InvalidateProjectionMatrix();
    }
}

float PerspectiveCamera::GetFieldOfView() const { return this->m_field_of_view; }

glm::mat4 PerspectiveCamera::CalculateProjectionMatrix() const {
    return glm::perspective(
        glm::radians(this->m_field_of_view), this->m_aspect_ratio, this->m_near_plane, this->m_far_plane
    );
}

DUSK_NAMESPACE_END
