#ifndef _DUSK_RENDERER_SHADER_HPP_
#define _DUSK_RENDERER_SHADER_HPP_

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The interface class for renderer and rendering API related to shader.
class Shader {
protected:
    unsigned int m_shader_id;

public:
    virtual ~Shader() = default;

public:
    /// @brief Bind the shader for rendering.
    virtual void bind() const = 0;

    /// @brief Unbind the shader for stoping rendering.
    virtual void unbind() const = 0;

    /// @brief Set value of uniform variables
    virtual void set_int(std::string const& name, int val) const = 0;
    virtual void set_int_array(std::string const& name, int* vals, uint32_t count) const = 0;
    virtual void set_float(std::string const& name, float val) const = 0;
    virtual void set_vec2(std::string const& name, glm::vec2 const& val) const = 0;
    virtual void set_vec3(std::string const& name, glm::vec3 const& val) const = 0;
    virtual void set_vec4(std::string const& name, glm::vec4 const& val) const = 0;
    virtual void set_mat2(std::string const& name, glm::mat2 const& val) const = 0;
    virtual void set_mat3(std::string const& name, glm::mat3 const& val) const = 0;
    virtual void set_mat4(std::string const& name, glm::mat4 const& val) const = 0;

    /// @brief Create a shader based on the given vertex and fragment shader code.
    static std::shared_ptr<Shader> create(std::string const& vs, std::string const& fs);
};

class ShaderLibrary {
public:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;

public:
    void add(std::string const& name, std::shared_ptr<Shader> shader);
    bool exists(std::string const& name) const;
    std::size_t size() const;
    /// @brief A pointer to accessing the shader.
    std::shared_ptr<Shader> get(std::string const& name);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_SHADER_HPP_
