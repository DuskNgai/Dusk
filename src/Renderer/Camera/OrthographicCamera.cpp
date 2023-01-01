#include <Dusk/Renderer/Camera/OrthographicCamera.hpp>

DUSK_NAMESPACE_BEGIN

OrthographicCamera::OrthographicCamera(
    glm::vec3 look_from, glm::vec3 look_to, glm::vec3 look_up,
    float near_plane, float far_plane, float aspect_ratio,
    float width
)
    : Camera(look_from, look_to, look_up, near_plane, far_plane, aspect_ratio)
    , m_width(width) {}

OrthographicCamera* OrthographicCamera::clone() const {
    return new OrthographicCamera(*this);
}

void OrthographicCamera::SetWidth(float val) {
    if (this->m_width != val) {
        this->m_width = val;
        this->InvalidateProjectionMatrix();
    }
}

float OrthographicCamera::GetWidth() const { return this->m_width; }

glm::vec4 OrthographicCamera::GetClipPositionFromNDC(glm::vec3 const& ndc_coords) const {
    return glm::vec4{ndc_coords, 1.0f};
}

glm::mat4 OrthographicCamera::CalculateProjectionMatrix() const {
    float half_width = this->m_width * 0.5f;
    float half_height = half_width / this->m_aspect_ratio;
    return glm::ortho(
        -half_width, half_width, -half_height, half_height, this->m_near_plane, this->m_far_plane
    );
}

DUSK_NAMESPACE_END
