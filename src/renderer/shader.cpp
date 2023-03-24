#include <dusk/assert.hpp>
#include <dusk/log.hpp>
#include <dusk/renderer/renderer.hpp>
#include <dusk/renderer/opengl/opengl-shader.hpp>

DUSK_NAMESPACE_BEGIN

//! Shader
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
//! Shader

//! ShaderLibrary
void ShaderLibrary::add(std::string const& name, std::shared_ptr<Shader> shader) {
    if (exists(name)) {
        DUSK_CORE_WARN("ShaderLibrary::add: Shader with name '{}' already exists, ignore it.", name);
        return;
    }
    this->m_shaders[name] = shader;
}

bool ShaderLibrary::exists(std::string const& name) const {
    return this->m_shaders.find(name) != this->m_shaders.end();
}

std::size_t ShaderLibrary::size() const {
    return this->m_shaders.size();
}

std::shared_ptr<Shader> ShaderLibrary::get(std::string const& name) {
    if (!this->exists(name)) {
        DUSK_CORE_ERROR("ShaderLibrary::get: Shader '{}' does not exist!", name);
        return nullptr;
    }
    return this->m_shaders[name];
}
//! ShaderLibrary

DUSK_NAMESPACE_END
