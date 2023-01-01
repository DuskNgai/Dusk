#ifndef _DUSK_RENDERER_OPENGL_SHADER_HPP_
#define _DUSK_RENDERER_OPENGL_SHADER_HPP_

#include <unordered_map>

#include <glad/glad.h>

#include <Dusk/Common.hpp>
#include <Dusk/Renderer/Shader.hpp>

DUSK_NAMESPACE_BEGIN

class OpenGLShader : public Shader {
private:
    // Caching the uniform variables that are visited before.
    mutable std::unordered_map<std::string, GLint> m_uniform_cache;

public:
    OpenGLShader(std::string const& vs, std::string const& fs);
    virtual ~OpenGLShader();

public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetInt(std::string const& name, int val) const override;
    virtual void SetIntArray(std::string const& name, int* vals, uint32_t count) const override;
    virtual void SetFloat(std::string const& name, float val) const override;
    virtual void SetVec2(std::string const& name, glm::vec2 const& val) const override;
    virtual void SetVec3(std::string const& name, glm::vec3 const& val) const override;
    virtual void SetVec4(std::string const& name, glm::vec4 const& val) const override;
    virtual void SetMat2(std::string const& name, glm::mat2 const& val) const override;
    virtual void SetMat3(std::string const& name, glm::mat3 const& val) const override;
    virtual void SetMat4(std::string const& name, glm::mat4 const& val) const override;

private:
    /// @brief Get a uniform variable's location according to its name.
    GLint GetUniformLocation(std::string const& name) const;

    /// @brief Compile a shader program.
    GLuint CompileShader(std::string const& code, GLenum shader_type) const;

    /// @brief Link a shader program.
    void LinkShader(GLuint vertex_shader, GLuint fragment_shader) const;

#ifndef NDEBUG
    /// @brief Validate a shader program (only in debug mode).
    void ValidateShader() const;
#endif
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_SHADER_HPP_
