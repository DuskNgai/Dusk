#include <Dusk/Assert.hpp>
#include <Dusk/Renderer/OpenGL/OpenGLRendererAPI.hpp>

DUSK_NAMESPACE_BEGIN

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

RendererAPI::API RendererAPI::GetAPI() { return RendererAPI::s_API; }

// clang-format off
std::unique_ptr<RendererAPI> RendererAPI::Create() {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None:      DUSK_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:    return std::make_unique<OpenGLRendererAPI>();
        case RendererAPI::API::Vulkan:    DUSK_CORE_ASSERT(false, "RendererAPI::API::Vulkan is currently not supported!"); return nullptr;
        case RendererAPI::API::DirectX12: DUSK_CORE_ASSERT(false, "RendererAPI::API::DirectX12 is currently not supported!"); return nullptr;
        default: DUSK_CORE_ASSERT(false, "Unrecognized RendererAPI::API!"); return nullptr;
    }
}
// clang-format on

DUSK_NAMESPACE_END
