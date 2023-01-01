#include <glad/glad.h>

#include <Dusk/Renderer/OpenGL/OpenGLRendererAPI.hpp>

DUSK_NAMESPACE_BEGIN

void OpenGLRendererAPI::Init() {
    // Blending texture.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Depth test.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void OpenGLRendererAPI::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(glm::vec4 const& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::SetLineWidth(float width) {
    glLineWidth(width);
}

/// @bug: need carefully studied!
void OpenGLRendererAPI::DrawArrays(VertexArray const* vertex_array) {
    vertex_array->Bind();
    glDrawArrays(GL_LINE_STRIP, 0, vertex_array->GetIndexBuffer()->Size());
}

void OpenGLRendererAPI::DrawElements(VertexArray const* vertex_array, uint32_t count) {
    auto index_count = count == 0 ? vertex_array->GetIndexBuffer()->Size() : count;
    vertex_array->Bind();
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
}

DUSK_NAMESPACE_END
