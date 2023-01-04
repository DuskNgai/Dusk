#include <Dusk/Renderer/Camera/CameraUtils.hpp>
#include <Dusk/Renderer/Camera/OrthographicCamera.hpp>
#include <Dusk/Renderer/Camera/PerspectiveCamera.hpp>

DUSK_NAMESPACE_BEGIN

OrthographicCamera::OrthographicCamera(
    glm::vec3 look_from, glm::vec3 look_to, glm::vec3 look_up,
    float near_plane, float far_plane, float aspect_ratio,
    float width
)
    : Camera(look_from, look_to, look_up, near_plane, far_plane, aspect_ratio)
    , m_width(width) {}

OrthographicCamera* OrthographicCamera::Clone() const {
    return new OrthographicCamera(*this);
}

void OrthographicCamera::UpdateFrom(Camera const* other) {
    Camera::UpdateFrom(other);
    if (auto oc = dynamic_cast<OrthographicCamera const*>(other)) {
        this->SetWidth(oc->GetWidth());
    }
    else if (auto pc = dynamic_cast<PerspectiveCamera const*>(other)) {
        this->SetWidth(YFoVToWidth(pc->GetFieldOfView(), glm::distance(this->GetLookFrom(), this->GetLookTo()), this->GetAspectRatio()));
    }
}

void OrthographicCamera::Zoom(float delta) {
    float width = std::max(0.1f, std::min(this->GetWidth() + delta, 100.0f));
    this->SetWidth(width);
}

void OrthographicCamera::SetWidth(float val) {
    if (this->m_width != val) {
        this->m_width = val;
        this->InvalidateProjectionMatrix();
    }
}

float OrthographicCamera::GetWidth() const { return this->m_width; }

CameraType OrthographicCamera::GetCameraType() const { return CameraType::Orthographic; }

glm::vec4 OrthographicCamera::GetClipPositionFromNDC(glm::vec3 const& ndc_coords) const {
    return {ndc_coords, 1.0f};
}

glm::mat4 OrthographicCamera::CalculateProjectionMatrix() const {
    float half_width = this->m_width * 0.5f;
    float half_height = half_width / this->m_aspect_ratio;
    return glm::ortho(
        -half_width, half_width, -half_height, half_height, this->m_near_plane, this->m_far_plane
    );
}

DUSK_NAMESPACE_END
