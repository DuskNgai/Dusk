#include <dusk/assert.hpp>
#include <dusk/log.hpp>
#include <dusk/renderer/renderer.hpp>
#include <dusk/renderer/opengl/opengl-shader.hpp>

DUSK_NAMESPACE_BEGIN

// clang-format off
std::shared_ptr<Shader> Shader::create(std::string const& vs, std::string const& fs) {
    switch (RendererAPI::get_API()) {
        case RendererAPI::API::None:      DUSK_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:    return std::make_unique<OpenGLShader>(vs, fs);
        case RendererAPI::API::Vulkan:    DUSK_CORE_ASSERT(false, "RendererAPI::API::Vulkan is currently not supported!"); return nullptr;
        case RendererAPI::API::DirectX12: DUSK_CORE_ASSERT(false, "RendererAPI::API::DirectX12 is currently not supported!"); return nullptr;
        default: DUSK_CORE_ASSERT(false, "Unrecognized RendererAPI::API!"); return nullptr;
    }
}
// clang-format on

DUSK_NAMESPACE_END
