#include <Dusk/Renderer/Renderer.hpp>
#include <Dusk/Renderer/Renderer2D.hpp>

DUSK_NAMESPACE_BEGIN

std::unique_ptr<Renderer::RenderData> Renderer::s_render_data = std::make_unique<RenderData>();

void Renderer::Init() {
    RenderCommand::Init();
    Renderer2D::Init();
}

void Renderer::Shutdown() {
    Renderer2D::Shutdown();
}

void Renderer::BeginScene(Camera* camera) {
    Renderer::s_render_data->camera = camera;
}

void Renderer::EndScene() {}

// Temporal and free to change~
void Renderer::Submit(Shader const* shader, VertexArray const* vertex_array, glm::mat4 const& model) {
    auto vp = Renderer::s_render_data->camera->GetProjectionMatrix() * Renderer::s_render_data->camera->GetViewMatrix();
    shader->Bind();
    shader->SetMat4("u_ViewProjection", vp);
    shader->SetMat4("u_Model", model);

    vertex_array->Bind();
    RenderCommand::DrawElements(vertex_array);
}

DUSK_NAMESPACE_END
