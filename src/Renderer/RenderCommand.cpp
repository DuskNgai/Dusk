#include <Dusk/Renderer/RenderCommand.hpp>

DUSK_NAMESPACE_BEGIN

std::unique_ptr<RendererAPI> RenderCommand::s_render_api = RendererAPI::Create();

void RenderCommand::Init() {
    RenderCommand::s_render_api->Init();
}

void RenderCommand::Clear() {
    RenderCommand::s_render_api->Clear();
}

void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    RenderCommand::s_render_api->SetViewport(x, y, width, height);
}

void RenderCommand::SetClearColor(glm::vec4 const& color) {
    RenderCommand::s_render_api->SetClearColor(color);
}

void RenderCommand::SetLineWidth(float width) {
    RenderCommand::s_render_api->SetLineWidth(width);
}

void RenderCommand::DrawArrays(VertexArray const* vertex_array) {
    RenderCommand::s_render_api->DrawArrays(vertex_array);
}

void RenderCommand::DrawElements(VertexArray const* vertex_array, uint32_t count) {
    RenderCommand::s_render_api->DrawElements(vertex_array, count);
}

DUSK_NAMESPACE_END
