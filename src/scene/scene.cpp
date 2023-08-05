#include <dusk/scene/scene.hpp>

#include <glm/glm.hpp>

DUSK_NAMESPACE_BEGIN

Scene::Scene() {
    struct TransformComponent {
        glm::mat4 transform;
    };
    struct MeshComponent {
        glm::mat4 transform;
    };

    auto entity{ this->m_registry.create() };
    // This returns a **reference** to the component.
    auto& transform{ this->m_registry.emplace<TransformComponent>(entity, glm::mat4(1.0f)) };
}

DUSK_NAMESPACE_END
