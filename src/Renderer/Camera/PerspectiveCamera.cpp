#include <Dusk/Renderer/Camera/CameraUtils.hpp>
#include <Dusk/Renderer/Camera/OrthographicCamera.hpp>
#include <Dusk/Renderer/Camera/PerspectiveCamera.hpp>

DUSK_NAMESPACE_BEGIN

PerspectiveCamera::PerspectiveCamera(
    glm::vec3 look_from, glm::vec3 look_to, glm::vec3 look_up,
    float near_plane, float far_plane, float aspect_ratio,
    float field_of_view
)
    : Camera(look_from, look_to, look_up, near_plane, far_plane, aspect_ratio)
    , m_field_of_view(field_of_view) {}

PerspectiveCamera* PerspectiveCamera::Clone() const {
    return new PerspectiveCamera(*this);
}

void PerspectiveCamera::UpdateFrom(Camera const* other) {
    Camera::UpdateFrom(other);
    if (auto pc = dynamic_cast<PerspectiveCamera const*>(other)) {
        this->SetFieldOfView(pc->GetFieldOfView());
    }
    else if (auto oc = dynamic_cast<OrthographicCamera const*>(other)) {
        this->SetFieldOfView(WidthToYFoV(oc->GetWidth(), glm::distance(this->GetLookFrom(), this->GetLookTo()), this->GetAspectRatio()));
    }
}

void PerspectiveCamera::Zoom(float delta) {
    float fov = std::max(0.1f, std::min(this->GetFieldOfView() + delta, 100.0f));
    this->SetFieldOfView(fov);
}

void PerspectiveCamera::SetFieldOfView(float degrees) {
    if (this->m_field_of_view != degrees) {
        this->m_field_of_view = degrees;
        this->InvalidateProjectionMatrix();
    }
}

float PerspectiveCamera::GetFieldOfView() const { return this->m_field_of_view; }

CameraType PerspectiveCamera::GetCameraType() const { return CameraType::Perspective; }

glm::mat4 PerspectiveCamera::CalculateProjectionMatrix() const {
    return glm::perspective(
        glm::radians(this->m_field_of_view), this->m_aspect_ratio, this->m_near_plane, this->m_far_plane
    );
}

DUSK_NAMESPACE_END
