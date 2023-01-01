#include <Dusk/Assert.hpp>
#include <Dusk/Log.hpp>
#include <Dusk/Renderer/RendererAPI.hpp>
#include <Dusk/Renderer/OpenGL/OpenGLTexture.hpp>

DUSK_NAMESPACE_BEGIN

//! Texture

//! Texture

//! Texture2D
// clang-format off
std::shared_ptr<Texture2D> Texture2D::Create(std::string const& path) {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None:      DUSK_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLTexture2D>(path);
        case RendererAPI::API::Vulkan:    DUSK_CORE_ASSERT(false, "RendererAPI::API::Vulkan is currently not supported!"); return nullptr;
        case RendererAPI::API::DirectX12: DUSK_CORE_ASSERT(false, "RendererAPI::API::DirectX12 is currently not supported!"); return nullptr;
        default: DUSK_CORE_ASSERT(false, "Unrecognized RendererAPI::API!"); return nullptr;
    }
}

std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None:      DUSK_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLTexture2D>(width, height);
        case RendererAPI::API::Vulkan:    DUSK_CORE_ASSERT(false, "RendererAPI::API::Vulkan is currently not supported!"); return nullptr;
        case RendererAPI::API::DirectX12: DUSK_CORE_ASSERT(false, "RendererAPI::API::DirectX12 is currently not supported!"); return nullptr;
        default: DUSK_CORE_ASSERT(false, "Unrecognized RendererAPI::API!"); return nullptr;
    }
}
// clang-format on
//! Texture2D

DUSK_NAMESPACE_END
