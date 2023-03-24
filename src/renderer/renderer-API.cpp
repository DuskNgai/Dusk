#include <dusk/assert.hpp>
#include <dusk/renderer/opengl/opengl-renderer-API.hpp>

DUSK_NAMESPACE_BEGIN

RendererAPI::API RendererAPI::s_API{ RendererAPI::API::OpenGL };

RendererAPI::API RendererAPI::get_API() { return RendererAPI::s_API; }

// clang-format off
std::unique_ptr<RendererAPI> RendererAPI::create() {
    switch (RendererAPI::get_API()) {
        case RendererAPI::API::None:      DUSK_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:    return std::make_unique<OpenGLRendererAPI>();
        case RendererAPI::API::Vulkan:    DUSK_CORE_ASSERT(false, "RendererAPI::API::Vulkan is currently not supported!"); return nullptr;
        case RendererAPI::API::DirectX12: DUSK_CORE_ASSERT(false, "RendererAPI::API::DirectX12 is currently not supported!"); return nullptr;
        default: DUSK_CORE_ASSERT(false, "Unrecognized RendererAPI::API!"); return nullptr;
    }
}
// clang-format on

DUSK_NAMESPACE_END
