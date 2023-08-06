#ifndef _DUSK_SCENE_SCENE_HPP_
#define _DUSK_SCENE_SCENE_HPP_

#include <entt/entt.hpp>

#include <dusk/common.hpp>
#include <dusk/scene/component/component.hpp>

DUSK_NAMESPACE_BEGIN

class Entity;

class Scene {
private:
    entt::registry m_registry;

public:
    Scene() = default;
    ~Scene() = default;

public:
    void on_update();

    Entity create_entity();
    entt::registry& get_registry();
};

DUSK_NAMESPACE_END

#endif // !_DUSK_SCENE_SCENE_HPP_
