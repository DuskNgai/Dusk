#ifndef _DUSK_SCENE_COMPONENT_COMPONENT_HPP_
#define _DUSK_SCENE_COMPONENT_COMPONENT_HPP_

#include <string>

#include <glm/glm.hpp>

#include <dusk/common.hpp>
#include <dusk/scene/camera/camera.hpp>

DUSK_NAMESPACE_BEGIN

struct CameraComponent {
    Camera* camera{ nullptr };
    // If true, this camera will be used for rendering.
    bool primary{ true };

    bool is_primary() const { return this->primary; }
};

struct SpriteComponent {
    glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };
};

struct TagComponent {
    std::string tag;
};

struct TransformComponent {
    glm::mat4 transform{ 1.0f };
};

DUSK_NAMESPACE_END

#endif // !_DUSK_SCENE_COMPONENT_COMPONENT_HPP_
