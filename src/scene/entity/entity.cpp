#include <dusk/scene/entity/entity.hpp>

DUSK_NAMESPACE_BEGIN

Entity::Entity(entt::entity entity, Scene* scene)
    : m_entity{ entity }
    , m_scene{ scene } {}

DUSK_NAMESPACE_END
