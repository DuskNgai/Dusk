#ifndef _DUSK_RENDERER_OPENGL_SHADER_HPP_
#define _DUSK_RENDERER_OPENGL_SHADER_HPP_

#include <unordered_map>

#include <glad/glad.h>

#include <dusk/common.hpp>
#include <dusk/renderer/shader.hpp>

DUSK_NAMESPACE_BEGIN

class OpenGLShader : public Shader {
private:
    // Caching the uniform variables that are visited before.
    mutable std::unordered_map<std::string, GLint> m_uniform_cache;

public:
    OpenGLShader(std::string const& vs, std::string const& fs);
    virtual ~OpenGLShader();

public:
    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void set_int(std::string const& name, int val) const override;
    virtual void set_int_array(std::string const& name, int* vals, uint32_t count) const override;
    virtual void set_float(std::string const& name, float val) const override;
    virtual void set_vec2(std::string const& name, glm::vec2 const& val) const override;
    virtual void set_vec3(std::string const& name, glm::vec3 const& val) const override;
    virtual void set_vec4(std::string const& name, glm::vec4 const& val) const override;
    virtual void set_mat2(std::string const& name, glm::mat2 const& val) const override;
    virtual void set_mat3(std::string const& name, glm::mat3 const& val) const override;
    virtual void set_mat4(std::string const& name, glm::mat4 const& val) const override;

private:
    /// @brief Get a uniform variable's location according to its name.
    GLint get_uniform_location(std::string const& name) const;

    GLuint compile_shader(std::string const& code, GLenum shader_type) const;
    void link_shader(GLuint vertex_shader, GLuint fragment_shader) const;
#ifndef NDEBUG
    void validate_shader() const;
#endif
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_SHADER_HPP_
