#include <Dusk/Assert.hpp>
#include <Dusk/Log.hpp>
#include <Dusk/Renderer/Renderer.hpp>
#include <Dusk/Renderer/OpenGL/OpenGLShader.hpp>

DUSK_NAMESPACE_BEGIN

//! Shader
// clang-format off
std::unique_ptr<Shader> Shader::Create(std::string const& vs, std::string const& fs) {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None:      DUSK_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:    return std::make_unique<OpenGLShader>(vs, fs);
        case RendererAPI::API::Vulkan:    DUSK_CORE_ASSERT(false, "RendererAPI::API::Vulkan is currently not supported!"); return nullptr;
        case RendererAPI::API::DirectX12: DUSK_CORE_ASSERT(false, "RendererAPI::API::DirectX12 is currently not supported!"); return nullptr;
        default: DUSK_CORE_ASSERT(false, "Unrecognized RendererAPI::API!"); return nullptr;
    }
}
// clang-format on
//! Shader

//! ShaderLibrary
void ShaderLibrary::Add(std::string const& name, std::unique_ptr<Shader> shader) {
    if (Exists(name)) {
        DUSK_CORE_WARN("ShaderLibrary::Add: Shader with name '{}' already exists, ignore it.", name);
        return;
    }
    this->m_shaders[name] = std::move(shader);
}

bool ShaderLibrary::Exists(std::string const& name) const {
    return this->m_shaders.find(name) != this->m_shaders.end();
}

std::size_t ShaderLibrary::Size() const {
    return this->m_shaders.size();
}

Shader const* ShaderLibrary::Get(std::string const& name) {
    if (!this->Exists(name)) {
        DUSK_CORE_ERROR("ShaderLibrary::Get: Shader '{}' does not exist!", name);
        return nullptr;
    }
    return this->m_shaders[name].get();
}
//! ShaderLibrary

DUSK_NAMESPACE_END
