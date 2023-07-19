#ifndef _DUSK_RENDERER_OPENGL_SHADER_HPP_
#define _DUSK_RENDERER_OPENGL_SHADER_HPP_

#include <map>

#include <glad/gl.h>

#include <dusk/common.hpp>
#include <dusk/renderer/shader.hpp>

DUSK_NAMESPACE_BEGIN

class OpenGLShader : public Shader {
private:
    // Caching the uniform variables that are visited before.
    mutable std::map<std::string, GLint, std::less<void>> m_uniform_cache;

public:
    OpenGLShader(std::string const& vs, std::string const& fs);
    virtual ~OpenGLShader();

public:
    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void set_int(std::string_view name, int val) const override;
    virtual void set_int_array(std::string_view name, int const* vals, uint32_t count) const override;
    virtual void set_float(std::string_view name, float val) const override;
    virtual void set_vec2(std::string_view name, glm::vec2 const& val) const override;
    virtual void set_vec3(std::string_view name, glm::vec3 const& val) const override;
    virtual void set_vec4(std::string_view name, glm::vec4 const& val) const override;
    virtual void set_mat2(std::string_view name, glm::mat2 const& val) const override;
    virtual void set_mat3(std::string_view name, glm::mat3 const& val) const override;
    virtual void set_mat4(std::string_view name, glm::mat4 const& val) const override;

private:
    /// @brief Get a uniform variable's location according to its name.
    GLint get_uniform_location(std::string_view name) const;

    GLuint compile_shader(std::string const& code, GLenum shader_type) const;
    void link_shader(GLuint vertex_shader, GLuint fragment_shader) const;
#ifndef NDEBUG
    void validate_shader() const;
#endif
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_SHADER_HPP_
