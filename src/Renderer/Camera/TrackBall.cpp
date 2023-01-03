#include <Dusk/Renderer/Input.hpp>
#include <Dusk/Renderer/Camera/TrackBall.hpp>
#include <Dusk/Utils/Timer.hpp>

DUSK_NAMESPACE_BEGIN

float const TrackBall::TRANSLATION_SPEED = 2.5f;
float const TrackBall::ROTATION_SPEED = 0.5f;
float const TrackBall::ZOOM_SPEED = 1.0f;

TrackBall::TrackBall(std::unique_ptr<Camera> camera)
    : m_camera(std::move(camera)) {}

void TrackBall::OnUpdate() {
    auto dt = Timer::GetDeltaTime();

    if (Input::IsKeyPressed(KeyCode::Up) or Input::IsKeyPressed(KeyCode::W)) {
        this->MoveUp(dt);
    }
    if (Input::IsKeyPressed(KeyCode::Left) or Input::IsKeyPressed(KeyCode::A)) {
        this->MoveLeft(dt);
    }
    if (Input::IsKeyPressed(KeyCode::Down) or Input::IsKeyPressed(KeyCode::S)) {
        this->MoveDown(dt);
    }
    if (Input::IsKeyPressed(KeyCode::Right) or Input::IsKeyPressed(KeyCode::D)) {
        this->MoveRight(dt);
    }
    if (Input::IsKeyPressed(KeyCode::Q)) {
        this->MoveForward(dt);
    }
    if (Input::IsKeyPressed(KeyCode::E)) {
        this->MoveBackward(dt);
    }
}

void TrackBall::OnEvent(EventBase& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseMovedEvent>(DUSK_BIND_CLASS_FN(TrackBall::OnMouseMoved));
    dispatcher.Dispatch<MouseScrolledEvent>(DUSK_BIND_CLASS_FN(TrackBall::OnMouseScrolled));
    dispatcher.Dispatch<MouseButtonPressedEvent>(DUSK_BIND_CLASS_FN(TrackBall::OnMouseButtonPressed));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(DUSK_BIND_CLASS_FN(TrackBall::OnMouseButtonReleased));
    dispatcher.Dispatch<WindowResizeEvent>(DUSK_BIND_CLASS_FN(TrackBall::OnWindowResize));
}

bool TrackBall::OnMouseMoved(MouseMovedEvent& e) {
    this->Rotate(e.GetNDCX(), e.GetNDCY());
    return false;
}

bool TrackBall::OnMouseScrolled(MouseScrolledEvent& e) {
    this->Zoom(e.GetYOffset());
    return false;
}

bool TrackBall::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
    if (e.GetMouseButton() == MouseCode::ButtonLeft) {
        this->m_is_mouse_being_pressed = true;
    }
    return false;
}

bool TrackBall::OnMouseButtonReleased(MouseButtonReleasedEvent& e) {
    if (e.GetMouseButton() == MouseCode::ButtonLeft) {
        this->m_is_mouse_being_pressed = false;
    }
    return false;
}

bool TrackBall::OnWindowResize(WindowResizeEvent& e) {
    this->SetAspectRatio((float)e.GetWidth() / (float)e.GetHeight());
    return false;
}

Camera* TrackBall::GetCamera() { return this->m_camera.get(); }

void TrackBall::SetLookFrom(glm::vec3 val) { this->m_camera->SetLookFrom(val); }
void TrackBall::SetLookTo(glm::vec3 val) { this->m_camera->SetLookTo(val); }
void TrackBall::SetLookUp(glm::vec3 val) { this->m_camera->SetLookUp(val); }
void TrackBall::SetLook(glm::vec3 look_from, glm::vec3 look_to, glm::vec3 look_up) {
    this->SetLookFrom(look_from);
    this->SetLookTo(look_to);
    this->SetLookUp(look_up);
}
void TrackBall::SetNearPlane(float val) { this->m_camera->SetNearPlane(val); }
void TrackBall::SetFarPlane(float val) { this->m_camera->SetFarPlane(val); }
void TrackBall::SetAspectRatio(float val) { this->m_camera->SetAspectRatio(val); }
void TrackBall::SetCameraType(CameraType type) {
    if (this->GetCameraType() != type) {
        auto new_camera = Camera::Create(type);
        new_camera->UpdateFrom(this->GetCamera());
        this->m_camera = std::move(new_camera);
    }
}

glm::vec3 TrackBall::GetLookFrom() const { return this->m_camera->GetLookFrom(); }
glm::vec3 TrackBall::GetLookTo() const { return this->m_camera->GetLookTo(); }
glm::vec3 TrackBall::GetLookUp() const { return this->m_camera->GetLookUp(); }
glm::vec3 TrackBall::GetLookForward() const {
    return glm::normalize(this->GetLookTo() - this->GetLookFrom());
}
glm::vec3 TrackBall::GetLookRight() const {
    return glm::normalize(glm::cross(this->GetLookTo() - this->GetLookFrom(), this->GetLookUp()));
}
float TrackBall::GetNearPlane() const { return this->m_camera->GetNearPlane(); }
float TrackBall::GetFarPlane() const { return this->m_camera->GetFarPlane(); }
float TrackBall::GetAspectRatio() const { return this->m_camera->GetAspectRatio(); }
CameraType TrackBall::GetCameraType() const { return this->m_camera->GetCameraType(); }

void TrackBall::MoveLeft(float dt) {
    glm::vec3 right = this->GetLookRight() * TrackBall::TRANSLATION_SPEED * dt;

    this->SetLookFrom(this->GetLookFrom() - right);
    this->SetLookTo(this->GetLookTo() - right);
}

void TrackBall::MoveRight(float dt) {
    glm::vec3 right = this->GetLookRight() * TrackBall::TRANSLATION_SPEED * dt;

    this->SetLookFrom(this->GetLookFrom() + right);
    this->SetLookTo(this->GetLookTo() + right);
}

void TrackBall::MoveUp(float dt) {
    glm::vec3 up = this->GetLookUp() * TrackBall::TRANSLATION_SPEED * dt;

    this->SetLookFrom(this->GetLookFrom() + up);
    this->SetLookTo(this->GetLookTo() + up);
}

void TrackBall::MoveDown(float dt) {
    glm::vec3 up = this->GetLookUp() * TrackBall::TRANSLATION_SPEED * dt;

    this->SetLookFrom(this->GetLookFrom() - up);
    this->SetLookTo(this->GetLookTo() - up);
}

void TrackBall::MoveForward(float dt) {
    glm::vec3 forward = this->GetLookForward() * TrackBall::TRANSLATION_SPEED * dt;

    this->SetLookFrom(this->GetLookFrom() + forward);
    this->SetLookTo(this->GetLookTo() + forward);
}

void TrackBall::MoveBackward(float dt) {
    glm::vec3 forward = this->GetLookForward() * TrackBall::TRANSLATION_SPEED * dt;

    this->SetLookFrom(this->GetLookFrom() - forward);
    this->SetLookTo(this->GetLookTo() - forward);
}

glm::mat4 TrackBall::Pitch(float radians) const {
    // Translate to origin, then rotate around local x-axis, then translate back.
    return glm::translate(glm::mat4{1.0f}, this->GetLookFrom()) * glm::rotate(glm::mat4{1.0f}, radians, this->GetLookRight()) * glm::translate(glm::mat4{1.0f}, -this->GetLookFrom());
}

glm::mat4 TrackBall::Yaw(float radians) const {
    // Translate to origin, then rotate around local y-axis, then translate back.
    return glm::translate(glm::mat4{1.0f}, this->GetLookFrom()) * glm::rotate(glm::mat4{1.0f}, radians, this->GetLookUp()) * glm::translate(glm::mat4{1.0f}, -this->GetLookFrom());
}

glm::mat4 TrackBall::Roll(float radians) const {
    // Translate to origin, then rotate around local z-axis, then translate back.
    return glm::translate(glm::mat4{1.0f}, this->GetLookFrom()) * glm::rotate(glm::mat4{1.0f}, radians, this->GetLookForward()) * glm::translate(glm::mat4{1.0f}, -this->GetLookFrom());
}

// TODO: Change to quaternion-based rotation.
void TrackBall::Rotate(float ndc_x, float ndc_y) {
    glm::vec3 ndc = glm::vec3(ndc_x, ndc_y, 1.0f);

    if (this->m_is_mouse_being_pressed) {
        glm::vec3 from = this->GetLookFrom();
        glm::vec3 to = this->GetLookTo();
        glm::vec3 diff = (ndc - this->m_last_ndc) * TrackBall::ROTATION_SPEED;
        glm::mat4 yaw = this->Yaw(diff.x);
        glm::mat4 pitch = this->Pitch(diff.y);
        glm::vec3 new_to = glm::vec3(yaw * pitch * glm::vec4(to, 1.0f));
        glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 new_view = glm::normalize(new_to - from);
        glm::vec3 new_right = glm::normalize(glm::cross(new_view, world_up));
        glm::vec3 new_up = glm::normalize(glm::cross(new_right, new_view));
        this->SetLook(from, new_to, new_up);
    }
    this->m_last_ndc = ndc;
}

void TrackBall::Zoom(float offset) {
    float delta = -offset * TrackBall::ZOOM_SPEED;
    this->GetCamera()->Zoom(delta);
}

DUSK_NAMESPACE_END
