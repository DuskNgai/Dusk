#ifndef _DUSK_RENDERER_SHADER_HPP_
#define _DUSK_RENDERER_SHADER_HPP_

#include <string_view>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief The interface class for renderer and rendering API related to shader.
class Shader {
protected:
    unsigned int m_shader_id;

public:
    virtual ~Shader() = default;

public:
    virtual void bind() const = 0;

    virtual void unbind() const = 0;

    virtual void set_int(std::string_view name, int val) const = 0;
    virtual void set_int_array(std::string_view name, int const* vals, uint32_t count) const = 0;
    virtual void set_float(std::string_view name, float val) const = 0;
    virtual void set_vec2(std::string_view name, glm::vec2 const& val) const = 0;
    virtual void set_vec3(std::string_view name, glm::vec3 const& val) const = 0;
    virtual void set_vec4(std::string_view name, glm::vec4 const& val) const = 0;
    virtual void set_mat2(std::string_view name, glm::mat2 const& val) const = 0;
    virtual void set_mat3(std::string_view name, glm::mat3 const& val) const = 0;
    virtual void set_mat4(std::string_view name, glm::mat4 const& val) const = 0;

    static std::shared_ptr<Shader> create(std::string const& vs, std::string const& fs);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_SHADER_HPP_
