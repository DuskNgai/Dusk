#include <glad/gl.h>

#include <dusk/assert.hpp>
#include <dusk/renderer/opengl/opengl-renderer-API.hpp>

DUSK_NAMESPACE_BEGIN

void OpenGLRendererAPI::initialize() {
    this->enable_render_test(RenderTest::DepthTest);
    // this->enable_render_test(RenderTest::StencilTest);
    this->enable_render_test(RenderTest::BlendTest);
    this->enable_render_test(RenderTest::MultiSample);
}

void OpenGLRendererAPI::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGLRendererAPI::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
}

void OpenGLRendererAPI::enable_render_test(RenderTest test) {
    switch (test) {
        case RenderTest::DepthTest:
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            break;
        case RenderTest::StencilTest:
            glEnable(GL_STENCIL_TEST);
            break;
        case RenderTest::BlendTest:
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case RenderTest::MultiSample:
            glEnable(GL_MULTISAMPLE);
            break;
        default:
            DUSK_CORE_ASSERT(false, "Unknown render test!");
            break;
    }
}

void OpenGLRendererAPI::disable_render_test(RenderTest test) {
    switch (test) {
        case RenderTest::DepthTest:
            glDisable(GL_DEPTH_TEST);
            break;
        case RenderTest::StencilTest:
            glDisable(GL_STENCIL_TEST);
            break;
        case RenderTest::BlendTest:
            glDisable(GL_BLEND);
            break;
        case RenderTest::MultiSample:
            glDisable(GL_MULTISAMPLE);
            break;
        default:
            DUSK_CORE_ASSERT(false, "Unknown render test!");
            break;
    }
}

void OpenGLRendererAPI::set_clear_color(glm::vec4 const& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::set_line_width(float width) {
    glLineWidth(width);
}

/// @bug: need carefully studied!
void OpenGLRendererAPI::draw_arrays(VertexArray const* vertex_array) {
    vertex_array->bind();
    glDrawArrays(GL_LINE_STRIP, 0, vertex_array->get_index_buffer()->size());
}

void OpenGLRendererAPI::draw_elements(VertexArray const* vertex_array, uint32_t count) {
    auto index_count{ count == 0 ? vertex_array->get_index_buffer()->size() : count };
    vertex_array->bind();
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
}

DUSK_NAMESPACE_END
