#include <dusk/utils/timer.hpp>
#include <dusk/renderer/input.hpp>
#include <dusk/scene/camera/track-ball.hpp>

DUSK_NAMESPACE_BEGIN

float const TrackBall::TRANSLATION_SPEED = 2.5f;
float const TrackBall::ROTATION_SPEED = 0.5f;
float const TrackBall::ZOOM_SPEED = 1.0f;

TrackBall::TrackBall(std::unique_ptr<Camera> camera)
    : m_camera{ std::move(camera) } {}

void TrackBall::on_update() {
    auto dt{ Timer::get_delta_time() };

    if (Input::is_key_pressed(KeyCode::Up) or Input::is_key_pressed(KeyCode::W)) {
        this->move_up(dt);
    }
    if (Input::is_key_pressed(KeyCode::Left) or Input::is_key_pressed(KeyCode::A)) {
        this->move_left(dt);
    }
    if (Input::is_key_pressed(KeyCode::Down) or Input::is_key_pressed(KeyCode::S)) {
        this->move_down(dt);
    }
    if (Input::is_key_pressed(KeyCode::Right) or Input::is_key_pressed(KeyCode::D)) {
        this->move_right(dt);
    }
    if (Input::is_key_pressed(KeyCode::Q)) {
        this->move_forward(dt);
    }
    if (Input::is_key_pressed(KeyCode::E)) {
        this->move_backward(dt);
    }
}

void TrackBall::on_event(EventBase& e) {
    if (e.m_handled) {
        return;
    }
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<MouseMovedEvent>(DUSK_BIND_CLASS_FN(TrackBall::on_mouse_moved));
    dispatcher.dispatch<MouseScrolledEvent>(DUSK_BIND_CLASS_FN(TrackBall::on_mouse_scrolled));
    dispatcher.dispatch<MouseButtonPressedEvent>(DUSK_BIND_CLASS_FN(TrackBall::on_mouse_button_pressed));
    dispatcher.dispatch<MouseButtonReleasedEvent>(DUSK_BIND_CLASS_FN(TrackBall::on_mouse_button_released));
    dispatcher.dispatch<WindowResizeEvent>(DUSK_BIND_CLASS_FN(TrackBall::on_window_resize));
}

bool TrackBall::on_mouse_moved(MouseMovedEvent& e) {
    this->rotate(e.get_ndc_x(), e.get_ndc_y());
    return false;
}

bool TrackBall::on_mouse_scrolled(MouseScrolledEvent& e) {
    this->zoom(e.get_offset_y());
    return false;
}

bool TrackBall::on_mouse_button_pressed(MouseButtonPressedEvent& e) {
    if (e.get_mouse_button() == MouseCode::ButtonLeft) {
        this->m_is_mouse_being_pressed = true;
    }
    return false;
}

bool TrackBall::on_mouse_button_released(MouseButtonReleasedEvent& e) {
    if (e.get_mouse_button() == MouseCode::ButtonLeft) {
        this->m_is_mouse_being_pressed = false;
    }
    return false;
}

bool TrackBall::on_window_resize(WindowResizeEvent& e) {
    this->set_aspect_ratio(static_cast<float>(e.get_width()) / static_cast<float>(e.get_height()));
    return false;
}

Camera* TrackBall::get_camera() { return this->m_camera.get(); }

void TrackBall::set_look_from(glm::vec3 const& val) { this->m_camera->set_look_from(val); }
void TrackBall::set_look_to(glm::vec3 const& val) { this->m_camera->set_look_to(val); }
void TrackBall::set_look_up(glm::vec3 const& val) { this->m_camera->set_look_up(val); }
void TrackBall::set_look(glm::vec3 const& look_from, glm::vec3 const& look_to, glm::vec3 const& look_up) {
    this->set_look_from(look_from);
    this->set_look_to(look_to);
    this->set_look_up(look_up);
}
void TrackBall::set_near_plane(float val) { this->m_camera->set_near_plane(val); }
void TrackBall::set_far_plane(float val) { this->m_camera->set_far_plane(val); }
void TrackBall::set_aspect_ratio(float val) { this->m_camera->set_aspect_ratio(val); }
void TrackBall::set_camera_type(CameraType type) {
    if (this->get_camera_type() != type) {
        auto new_camera{ Camera::create(type) };
        new_camera->update_from(this->get_camera());
        this->m_camera = std::move(new_camera);
    }
}

glm::vec3 TrackBall::get_look_from() const { return this->m_camera->get_look_from(); }
glm::vec3 TrackBall::get_look_to() const { return this->m_camera->get_look_to(); }
glm::vec3 TrackBall::get_look_up() const { return this->m_camera->get_look_up(); }
glm::vec3 TrackBall::get_look_forward() const {
    return glm::normalize(this->get_look_to() - this->get_look_from());
}
glm::vec3 TrackBall::get_look_right() const {
    return glm::normalize(glm::cross(this->get_look_to() - this->get_look_from(), this->get_look_up()));
}
float TrackBall::get_near_plane() const { return this->m_camera->get_near_plane(); }
float TrackBall::get_far_plane() const { return this->m_camera->get_far_plane(); }
float TrackBall::get_aspect_ratio() const { return this->m_camera->get_aspect_ratio(); }
CameraType TrackBall::get_camera_type() const { return this->m_camera->get_camera_type(); }

void TrackBall::move_left(float dt) {
    auto right{ this->get_look_right() * TrackBall::TRANSLATION_SPEED * dt };

    this->set_look_from(this->get_look_from() - right);
    this->set_look_to(this->get_look_to() - right);
}

void TrackBall::move_right(float dt) {
    auto right{ this->get_look_right() * TrackBall::TRANSLATION_SPEED * dt };

    this->set_look_from(this->get_look_from() + right);
    this->set_look_to(this->get_look_to() + right);
}

void TrackBall::move_up(float dt) {
    auto up{ this->get_look_up() * TrackBall::TRANSLATION_SPEED * dt };

    this->set_look_from(this->get_look_from() + up);
    this->set_look_to(this->get_look_to() + up);
}

void TrackBall::move_down(float dt) {
    auto up{ this->get_look_up() * TrackBall::TRANSLATION_SPEED * dt };

    this->set_look_from(this->get_look_from() - up);
    this->set_look_to(this->get_look_to() - up);
}

void TrackBall::move_forward(float dt) {
    auto forward{ this->get_look_forward() * TrackBall::TRANSLATION_SPEED * dt };

    this->set_look_from(this->get_look_from() + forward);
    this->set_look_to(this->get_look_to() + forward);
}

void TrackBall::move_backward(float dt) {
    auto forward{ this->get_look_forward() * TrackBall::TRANSLATION_SPEED * dt };

    this->set_look_from(this->get_look_from() - forward);
    this->set_look_to(this->get_look_to() - forward);
}

glm::mat4 TrackBall::pitch(float radians) const {
    // Translate to origin, then rotate around local x-axis, then translate back.
    return glm::translate(glm::mat4{ 1.0f }, this->get_look_from()) * glm::rotate(glm::mat4{ 1.0f }, radians, this->get_look_right()) * glm::translate(glm::mat4{ 1.0f }, -this->get_look_from());
}

glm::mat4 TrackBall::yaw(float radians) const {
    // Translate to origin, then rotate around local y-axis, then translate back.
    return glm::translate(glm::mat4{ 1.0f }, this->get_look_from()) * glm::rotate(glm::mat4{ 1.0f }, radians, this->get_look_up()) * glm::translate(glm::mat4{ 1.0f }, -this->get_look_from());
}

glm::mat4 TrackBall::roll(float radians) const {
    // Translate to origin, then rotate around local z-axis, then translate back.
    return glm::translate(glm::mat4{ 1.0f }, this->get_look_from()) * glm::rotate(glm::mat4{ 1.0f }, radians, this->get_look_forward()) * glm::translate(glm::mat4{ 1.0f }, -this->get_look_from());
}

// TODO: Change to quaternion-based rotation.
void TrackBall::rotate(float ndc_x, float ndc_y) {
    glm::vec3 ndc{ ndc_x, ndc_y, 1.0f };

    if (this->m_is_mouse_being_pressed) {
        glm::vec3 from{ this->get_look_from() };
        glm::vec3 to{ this->get_look_to() };
        glm::vec3 diff{ (ndc - this->m_last_ndc) * TrackBall::ROTATION_SPEED };
        glm::mat4 yaw{ this->yaw(diff.x) };
        glm::mat4 pitch{ this->pitch(diff.y) };
        glm::vec3 new_to{ glm::vec3(yaw * pitch * glm::vec4(to, 1.0f)) };
        glm::vec3 world_up{ 0.0f, 1.0f, 0.0f };
        glm::vec3 new_view{ glm::normalize(new_to - from) };
        glm::vec3 new_right{ glm::normalize(glm::cross(new_view, world_up)) };
        glm::vec3 new_up{ glm::normalize(glm::cross(new_right, new_view)) };
        this->set_look(from, new_to, new_up);
    }
    this->m_last_ndc = ndc;
}

void TrackBall::zoom(float offset) {
    auto delta{ -offset * TrackBall::ZOOM_SPEED };
    this->get_camera()->zoom(delta);
}

DUSK_NAMESPACE_END
