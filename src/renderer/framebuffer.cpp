#include <dusk/assert.hpp>
#include <dusk/renderer/renderer-API.hpp>
#include <dusk/renderer/opengl/opengl-framebuffer.hpp>

DUSK_NAMESPACE_BEGIN

// clang-format off
std::unique_ptr<Framebuffer> Framebuffer::create(uint32_t width, uint32_t height) {
    switch (RendererAPI::get_API()) {
        case RendererAPI::API::None:      DUSK_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:    return std::make_unique<OpenGLFramebuffer>(width, height);
        case RendererAPI::API::Vulkan:    DUSK_CORE_ASSERT(false, "RendererAPI::API::Vulkan is currently not supported!"); return nullptr;
        case RendererAPI::API::DirectX12: DUSK_CORE_ASSERT(false, "RendererAPI::API::DirectX12 is currently not supported!"); return nullptr;
        default: DUSK_CORE_ASSERT(false, "Unrecognized RendererAPI::API!"); return nullptr;
    }
}
// clang-format on

DUSK_NAMESPACE_END
