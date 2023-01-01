#include <Dusk/Renderer/Input.hpp>
#include <Dusk/Renderer/Camera/TrackBall.hpp>
#include <Dusk/Utils/Timer.hpp>

DUSK_NAMESPACE_BEGIN

float const TrackBall::TRANSLATION_SPEED = 2.5f;
float const TrackBall::ROTATION_SPEED = 2.5f;
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
    dispatcher.Dispatch<MouseScrolledEvent>(DUSK_BIND_CLASS_FN(TrackBall::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(DUSK_BIND_CLASS_FN(TrackBall::OnWindowResize));
}

bool TrackBall::OnMouseScrolled(MouseScrolledEvent& e) {
    this->Zoom(e.GetYOffset());
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

glm::vec3 TrackBall::GetLookFrom() const { return this->m_camera->GetLookFrom(); }
glm::vec3 TrackBall::GetLookTo() const { return this->m_camera->GetLookTo(); }
glm::vec3 TrackBall::GetLookUp() const { return this->m_camera->GetLookUp(); }
glm::vec3 TrackBall::GetLookRight() const {
    return glm::normalize(glm::cross(this->GetLookTo() - this->GetLookFrom(), this->GetLookUp()));
}
float TrackBall::GetNearPlane() const { return this->m_camera->GetNearPlane(); }
float TrackBall::GetFarPlane() const { return this->m_camera->GetFarPlane(); }
float TrackBall::GetAspectRatio() const { return this->m_camera->GetAspectRatio(); }

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
    glm::vec3 forward = glm::normalize(this->GetLookTo() - this->GetLookFrom()) * TrackBall::TRANSLATION_SPEED * dt;

    this->SetLookFrom(this->GetLookFrom() + forward);
    this->SetLookTo(this->GetLookTo() + forward);
}

void TrackBall::MoveBackward(float dt) {
    glm::vec3 forward = glm::normalize(this->GetLookTo() - this->GetLookFrom()) * TrackBall::TRANSLATION_SPEED * dt;

    this->SetLookFrom(this->GetLookFrom() - forward);
    this->SetLookTo(this->GetLookTo() - forward);
}

// Temporal code, do not use RTTI too frequently!
void TrackBall::Zoom(float offset) {
    static int camera_type{0};

    auto ptr = this->GetCamera();
    if (camera_type == 0) {
        if (typeid(*ptr) != typeid(PerspectiveCamera)) {
            this->m_camera.swap(this->m_orthographic_camera);
            this->m_camera.swap(this->m_perspective_camera);
            this->m_camera->UpdateFrom(this->m_orthographic_camera.get());
        }
    }
    else {
        if (typeid(*ptr) != typeid(OrthographicCamera)) {
            this->m_camera.swap(this->m_perspective_camera);
            this->m_camera.swap(this->m_orthographic_camera);
            this->m_camera->UpdateFrom(this->m_perspective_camera.get());
        }
    }

    ptr = this->GetCamera();
    if (typeid(*ptr) == typeid(PerspectiveCamera)) {
        auto fov = dynamic_cast<PerspectiveCamera*>(ptr)->GetFieldOfView() - offset * TrackBall::ZOOM_SPEED;
        fov = std::max(0.1f, std::min(fov, 100.0f));
        dynamic_cast<PerspectiveCamera*>(ptr)->SetFieldOfView(fov);
    }
    else {
        auto width = dynamic_cast<OrthographicCamera*>(ptr)->GetWidth() - offset * TrackBall::ZOOM_SPEED;
        width = std::max(0.1f, std::min(width, 100.0f));
        dynamic_cast<OrthographicCamera*>(ptr)->SetWidth(width);
    }
}

DUSK_NAMESPACE_END
