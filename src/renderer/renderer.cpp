#include <dusk/renderer/renderer.hpp>
#include <dusk/renderer/renderer-2D.hpp>

DUSK_NAMESPACE_BEGIN

std::unique_ptr<Renderer::RenderData> Renderer::s_render_data{ std::make_unique<RenderData>() };

void Renderer::init() {
    RenderCommand::init();
    Renderer2D::init();
}

void Renderer::shut_down() {
    Renderer2D::shut_down();
}

void Renderer::begin_scene(Camera* camera) {
    Renderer::s_render_data->camera = camera;
}

void Renderer::end_scene() {}

// Temporal and free to change~
void Renderer::submit(std::shared_ptr<Shader> const& shader, std::unique_ptr<VertexArray> const& vertex_array, glm::mat4 const& model) {
    shader->bind();
    shader->set_mat4("u_Projection", Renderer::s_render_data->camera->get_projection_matrix());
    shader->set_mat4("u_View", Renderer::s_render_data->camera->get_view_matrix());
    shader->set_mat4("u_Model", model);

    vertex_array->bind();
    RenderCommand::draw_elements(vertex_array.get());
}

DUSK_NAMESPACE_END
