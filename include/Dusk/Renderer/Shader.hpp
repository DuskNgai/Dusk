#ifndef _DUSK_RENDERER_SHADER_HPP_
#define _DUSK_RENDERER_SHADER_HPP_

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Dusk/Common.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The interface class for renderer and rendering API related to shader.
class Shader {
protected:
    unsigned int m_shader_id;

public:
    virtual ~Shader() = default;

public:
    static std::shared_ptr<Shader> Create(std::string const& vs, std::string const& fs);

    /// @brief Bind the shader for rendering.
    virtual void Bind() const = 0;

    /// @brief Unbind the shader for stoping rendering.
    virtual void Unbind() const = 0;

    /// @brief Set value of uniform variables
    virtual void SetInt(std::string const& name, int val) const = 0;
    virtual void SetIntArray(std::string const& name, int* vals, uint32_t count) const = 0;
    virtual void SetFloat(std::string const& name, float val) const = 0;
    virtual void SetVec2(std::string const& name, glm::vec2 const& val) const = 0;
    virtual void SetVec3(std::string const& name, glm::vec3 const& val) const = 0;
    virtual void SetVec4(std::string const& name, glm::vec4 const& val) const = 0;
    virtual void SetMat2(std::string const& name, glm::mat2 const& val) const = 0;
    virtual void SetMat3(std::string const& name, glm::mat3 const& val) const = 0;
    virtual void SetMat4(std::string const& name, glm::mat4 const& val) const = 0;
};

class ShaderLibrary {
public:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;

public:
    void Add(std::string const& name, std::shared_ptr<Shader> shader);
    bool Exists(std::string const& name) const;
    std::size_t Size() const;
    /// @brief A pointer to accessing the shader.
    std::shared_ptr<Shader> Get(std::string const& name);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_SHADER_HPP_
