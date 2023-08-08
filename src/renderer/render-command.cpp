#include <dusk/renderer/render-command.hpp>

DUSK_NAMESPACE_BEGIN

std::unique_ptr<RendererAPI> RenderCommand::s_render_api{ RendererAPI::create() };

void RenderCommand::initialize() {
    RenderCommand::s_render_api->initialize();
}

void RenderCommand::clear() {
    RenderCommand::s_render_api->clear();
}

void RenderCommand::enable_render_test(RenderTest test) {
    RenderCommand::s_render_api->enable_render_test(test);
}

void RenderCommand::disable_render_test(RenderTest test) {
    RenderCommand::s_render_api->disable_render_test(test);
}

void RenderCommand::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    RenderCommand::s_render_api->set_viewport(x, y, width, height);
}

void RenderCommand::set_clear_color(glm::vec4 const& color) {
    RenderCommand::s_render_api->set_clear_color(color);
}

void RenderCommand::set_line_width(float width) {
    RenderCommand::s_render_api->set_line_width(width);
}

void RenderCommand::draw_arrays(VertexArray const* vertex_array) {
    RenderCommand::s_render_api->draw_arrays(vertex_array);
}

void RenderCommand::draw_elements(VertexArray const* vertex_array, uint32_t count) {
    RenderCommand::s_render_api->draw_elements(vertex_array, count);
}

DUSK_NAMESPACE_END
