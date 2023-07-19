#ifndef _DUSK_RENDERER_CAMERA_TRACKBALL_HPP_
#define _DUSK_RENDERER_CAMERA_TRACKBALL_HPP_

#include <memory>

#include <dusk/core/event/key-event.hpp>
#include <dusk/core/event/mouse-event.hpp>
#include <dusk/core/event/window-event.hpp>
#include <dusk/scene/camera/camera.hpp>
#include <dusk/scene/camera/orthographic-camera.hpp>
#include <dusk/scene/camera/perspective-camera.hpp>

DUSK_NAMESPACE_BEGIN

class TrackBall {
protected:
    static float const TRANSLATION_SPEED;
    static float const ROTATION_SPEED;
    static float const ZOOM_SPEED;

    std::unique_ptr<Camera> m_camera;

    glm::vec3 m_last_ndc;
    bool m_is_mouse_being_pressed{ false };

public:
    TrackBall(std::unique_ptr<Camera> camera);
    ~TrackBall() = default;

public:
    void on_update();
    void on_event(EventBase& e);
    bool on_mouse_moved(MouseMovedEvent& e);
    bool on_mouse_scrolled(MouseScrolledEvent& e);
    bool on_mouse_button_pressed(MouseButtonPressedEvent& e);
    bool on_mouse_button_released(MouseButtonReleasedEvent& e);
    bool on_window_resize(WindowResizeEvent& e);

public:
    Camera* get_camera();

    void set_look_from(glm::vec3 const& val);
    void set_look_to(glm::vec3 const& val);
    void set_look_up(glm::vec3 const& val);
    void set_look(glm::vec3 const& look_from, glm::vec3 const& look_to, glm::vec3 const& look_up);
    void set_near_plane(float val);
    void set_far_plane(float val);
    void set_aspect_ratio(float val);
    /// @brief Change the camera of the trackball by type.
    /// If the type is the same, nothing happens.
    void set_camera_type(CameraType type);

    glm::vec3 get_look_from() const;
    glm::vec3 get_look_to() const;
    glm::vec3 get_look_up() const;
    glm::vec3 get_look_forward() const;
    glm::vec3 get_look_right() const;
    float get_near_plane() const;
    float get_far_plane() const;
    float get_aspect_ratio() const;
    CameraType get_camera_type() const;

private:
    void move_left(float dt);
    void move_right(float dt);
    void move_up(float dt);
    void move_down(float dt);
    void move_forward(float dt);
    void move_backward(float dt);

    glm::mat4 pitch(float radians) const;
    glm::mat4 yaw(float radians) const;
    glm::mat4 roll(float radians) const;
    void rotate(float ndc_x, float ndc_y);

    void zoom(float offset);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_CAMERA_TRACKBALL_HPP_
