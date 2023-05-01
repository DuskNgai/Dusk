#ifndef _DUSK_RENDERER_SHADER_HPP_
#define _DUSK_RENDERER_SHADER_HPP_

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <dusk/common.hpp>
#include <dusk/core/utils/indexed-map.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The interface class for renderer and rendering API related to shader.
class Shader {
protected:
    unsigned int m_shader_id;

public:
    virtual ~Shader() = default;

public:
    virtual void bind() const = 0;

    virtual void unbind() const = 0;

    virtual void set_int(std::string const& name, int val) const = 0;
    virtual void set_int_array(std::string const& name, int const* vals, uint32_t count) const = 0;
    virtual void set_float(std::string const& name, float val) const = 0;
    virtual void set_vec2(std::string const& name, glm::vec2 const& val) const = 0;
    virtual void set_vec3(std::string const& name, glm::vec3 const& val) const = 0;
    virtual void set_vec4(std::string const& name, glm::vec4 const& val) const = 0;
    virtual void set_mat2(std::string const& name, glm::mat2 const& val) const = 0;
    virtual void set_mat3(std::string const& name, glm::mat3 const& val) const = 0;
    virtual void set_mat4(std::string const& name, glm::mat4 const& val) const = 0;

    static std::shared_ptr<Shader> create(std::string const& vs, std::string const& fs);
};

class ShaderLibrary {
public:
    IndexedMap<std::string, std::shared_ptr<Shader>> m_shaders;

public:
    void emplace(std::string const& name, std::shared_ptr<Shader> shader);
    bool contains(std::string const& name) const;
    std::size_t size() const;

    /// @brief A pointer to accessing the shader.
    std::shared_ptr<Shader> get(std::string const& name) const;

    /// @brief A pair of name and pointer to accessing the shader.
    std::pair<std::string, std::shared_ptr<Shader>> get(std::size_t index) const;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_SHADER_HPP_
