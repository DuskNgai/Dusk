#include <dusk/renderer/renderer-2D.hpp>
#include <dusk/scene/scene.hpp>
#include <dusk/scene/entity/entity.hpp>

DUSK_NAMESPACE_BEGIN

void Scene::on_update() {
    // Find the main camera.
    Camera* main_camera{ nullptr };
    {
        auto view { this->m_registry.view<TransformComponent, CameraComponent>() };
        for (auto entity : view) {
            auto&& [transform, camera]{
                view.get<TransformComponent, CameraComponent>(entity)
            };

            if (camera.primary) {
                main_camera = camera.camera;
                break;
            }
        }
    }

    // Update all the transforms.
    if (main_camera) {
        dusk::Renderer2D::begin_scene(main_camera);

        auto view{ this->m_registry.view<TransformComponent, SpriteComponent>() };
        for (auto entity : view) {
            auto&& [transform, sprite]{
                view.get<TransformComponent, SpriteComponent>(entity)
            };

            Renderer2D::draw_quad(transform.transform, sprite.color);
        }

        dusk::Renderer2D::end_scene();
    }
}

Entity Scene::create_entity() {
    return { this->m_registry.create(), this };
}

entt::registry& Scene::get_registry() {
    return this->m_registry;
}

DUSK_NAMESPACE_END
