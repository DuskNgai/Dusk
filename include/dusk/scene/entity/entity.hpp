#ifndef _DUSK_SCENE_ENTITY_ENTITY_HPP_
#define _DUSK_SCENE_ENTITY_ENTITY_HPP_

#include <memory>

#include <entt/entt.hpp>

#include <dusk/assert.hpp>
#include <dusk/common.hpp>
#include <dusk/scene/scene.hpp>

DUSK_NAMESPACE_BEGIN

class Entity {
private:
    entt::entity m_entity{ entt::null };
    // Entity has no ownership of the scene.
    Scene* m_scene{ nullptr };

public:
    Entity() = default;
    Entity(entt::entity entity, Scene* scene);

public:
    template <typename T, typename... Args>
    T& add_component(Args&&... args) {
        DUSK_CORE_ASSERT(!has_component<T>(), "Entity already has component!");
        return this->m_scene->get_registry().emplace<T>(this->m_entity, std::forward<Args>(args)...);
    }

    template <typename T>
    T& get_component() {
        DUSK_CORE_ASSERT(has_component<T>(), "Entity does not have component!");
        return this->m_scene->get_registry().get<T>(this->m_entity);
    }

    template <typename T>
    bool has_component() {
        return this->m_scene->get_registry().any_of<T>(this->m_entity);
    }

    template <typename T>
    void remove_component() {
        DUSK_CORE_ASSERT(has_component<T>(), "Entity does not have component!");
        this->m_scene->get_registry().remove<T>(this->m_entity);
    }

    operator bool() const { return this->m_entity != entt::null; }
    operator entt::entity() const { return this->m_entity; }
    operator uint32_t() const { return (uint32_t)this->m_entity; }
};

DUSK_NAMESPACE_END

#endif // !_DUSK_SCENE_ENTITY_ENTITY_HPP_
