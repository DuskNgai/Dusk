#ifndef _DUSK_RENDERER_CAMERA_TRACKBALL_HPP_
#define _DUSK_RENDERER_CAMERA_TRACKBALL_HPP_

#include <memory>

#include <Dusk/Core/Event/KeyEvent.hpp>
#include <Dusk/Core/Event/MouseEvent.hpp>
#include <Dusk/Core/Event/WindowEvent.hpp>
#include <Dusk/Renderer/Camera/Camera.hpp>
#include <Dusk/Renderer/Camera/OrthographicCamera.hpp>
#include <Dusk/Renderer/Camera/PerspectiveCamera.hpp>

DUSK_NAMESPACE_BEGIN

class TrackBall {
protected:
    static float const TRANSLATION_SPEED;
    static float const ROTATION_SPEED;
    static float const ZOOM_SPEED;

    std::unique_ptr<Camera> m_camera;

    std::unique_ptr<Camera> m_orthographic_camera{std::make_unique<OrthographicCamera>()};
    std::unique_ptr<Camera> m_perspective_camera{std::make_unique<PerspectiveCamera>()};

public:
    TrackBall(std::unique_ptr<Camera> camera);
    ~TrackBall() = default;

public:
    void OnUpdate();
    void OnEvent(EventBase& e);
    bool OnMouseScrolled(MouseScrolledEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

public:
    Camera* GetCamera();

    void SetLookFrom(glm::vec3 val);
    void SetLookTo(glm::vec3 val);
    void SetLookUp(glm::vec3 val);
    void SetLook(glm::vec3 look_from, glm::vec3 look_to, glm::vec3 look_up);
    void SetNearPlane(float val);
    void SetFarPlane(float val);
    void SetAspectRatio(float val);

    glm::vec3 GetLookFrom() const;
    glm::vec3 GetLookTo() const;
    glm::vec3 GetLookUp() const;
    glm::vec3 GetLookRight() const;
    float GetNearPlane() const;
    float GetFarPlane() const;
    float GetAspectRatio() const;

private:
    void MoveLeft(float dt);
    void MoveRight(float dt);
    void MoveUp(float dt);
    void MoveDown(float dt);
    void MoveForward(float dt);
    void MoveBackward(float dt);

    void Zoom(float offset);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_CAMERA_TRACKBALL_HPP_
