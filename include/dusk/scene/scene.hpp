#ifndef _DUSK_SCENE_SCENE_HPP_
#define _DUSK_SCENE_SCENE_HPP_

#include <entt/entt.hpp>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

class Scene {
private:
    entt::registry m_registry;

public:
    Scene();
    ~Scene();
};

DUSK_NAMESPACE_END

#endif // !_DUSK_SCENE_SCENE_HPP_
