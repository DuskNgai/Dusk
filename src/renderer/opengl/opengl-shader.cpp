#include <vector>

#include <dusk/assert.hpp>
#include <dusk/log.hpp>
#include <dusk/renderer/opengl/opengl-shader.hpp>

DUSK_NAMESPACE_BEGIN

OpenGLShader::OpenGLShader(std::string const& vs, std::string const& fs) {
    GLuint vertex_shader{ this->compile_shader(vs, GL_VERTEX_SHADER) };
    GLuint fragment_shader{ this->compile_shader(fs, GL_FRAGMENT_SHADER) };

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    this->m_shader_id = glCreateProgram();
    this->link_shader(vertex_shader, fragment_shader);
#ifndef NDEBUG
    this->validate_shader();
#endif
}

OpenGLShader::~OpenGLShader() {
    glDeleteProgram(this->m_shader_id);
}

void OpenGLShader::bind() const {
    glUseProgram(this->m_shader_id);
}

void OpenGLShader::unbind() const {
    glUseProgram(0);
}

void OpenGLShader::set_int(std::string_view name, int val) const {
    auto location{ this->get_uniform_location(name) };
    glUniform1i(location, val);
}

void OpenGLShader::set_int_array(std::string_view name, int const* vals, uint32_t count) const {
    auto location{ this->get_uniform_location(name) };
    glUniform1iv(location, count, vals);
}

void OpenGLShader::set_float(std::string_view name, float val) const {
    auto location{ this->get_uniform_location(name) };
    glUniform1f(location, val);
}

void OpenGLShader::set_vec2(std::string_view name, glm::vec2 const& val) const {
    auto location{ this->get_uniform_location(name) };
    glUniform2f(location, val.x, val.y);
}

void OpenGLShader::set_vec3(std::string_view name, glm::vec3 const& val) const {
    auto location{ this->get_uniform_location(name) };
    glUniform3f(location, val.x, val.y, val.z);
}

void OpenGLShader::set_vec4(std::string_view name, glm::vec4 const& val) const {
    auto location{ this->get_uniform_location(name) };
    glUniform4f(location, val.x, val.y, val.z, val.w);
}

void OpenGLShader::set_mat2(std::string_view name, glm::mat2 const& val) const {
    auto location{ this->get_uniform_location(name) };
    glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

void OpenGLShader::set_mat3(std::string_view name, glm::mat3 const& val) const {
    auto location{ this->get_uniform_location(name) };
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

void OpenGLShader::set_mat4(std::string_view name, glm::mat4 const& val) const {
    auto location{ this->get_uniform_location(name) };
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

GLint OpenGLShader::get_uniform_location(std::string_view name) const {
    // Check if the uniform is already in the cache
    auto it{ this->m_uniform_cache.find(name) };
    if (it != this->m_uniform_cache.end()) {
        return it->second;
    }
    else {
        std::string name_s{ name };
        auto location{ glGetUniformLocation(this->m_shader_id, name_s.c_str()) };

        if (location == -1) {
            DUSK_CORE_ERROR("Uniform \"{:s}\" not found", name);
        }

        this->m_uniform_cache.try_emplace(std::move(name_s), location);
        return location;
    }
}

GLuint OpenGLShader::compile_shader(std::string const& code, GLenum shader_type) const {
    // An vertex shader handle
    GLuint shader{ glCreateShader(shader_type) };

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    GLchar const* source{ code.c_str() };
    glShaderSource(shader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(shader);

    GLint is_compiled{ 0 };
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE) {
        GLint max_length{ 0 };
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

        // The max_length includes the NULL character
        std::vector<GLchar> info_log(max_length);
        glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);

        // We don't need the shader anymore.
        glDeleteShader(shader);

        // Use the info_log as you see fit.
        DUSK_CORE_ERROR(info_log.data());
        DUSK_CORE_ASSERT(false, "Shader compilation failed!");

        return 0;
    }
    return shader;
}

void OpenGLShader::link_shader(GLuint vertex_shader, GLuint fragment_shader) const {
    // Attach our shaders to our program
    glAttachShader(this->m_shader_id, vertex_shader);
    glAttachShader(this->m_shader_id, fragment_shader);

    // Link our program
    glLinkProgram(this->m_shader_id);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked{ 0 };
    glGetProgramiv(this->m_shader_id, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint max_length{ 0 };
        glGetProgramiv(this->m_shader_id, GL_INFO_LOG_LENGTH, &max_length);

        // The max_length includes the NULL character
        std::vector<GLchar> info_log(max_length);
        glGetProgramInfoLog(this->m_shader_id, max_length, &max_length, &info_log[0]);

        // We don't need the program anymore.
        glDeleteProgram(this->m_shader_id);
        // Don't leak shaders either.
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        // Use the info_log as you see fit.
        DUSK_CORE_ERROR(info_log.data());
        DUSK_CORE_ASSERT(false, "Program linking failed!");

        return;
    }

    // Mark the shaders for deletion.
    // They will be deleted when detached from the program.
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    // Always detach shaders after a successful link.
    glDetachShader(this->m_shader_id, vertex_shader);
    glDetachShader(this->m_shader_id, fragment_shader);
}

#ifndef NDEBUG
void OpenGLShader::validate_shader() const {
    glValidateProgram(this->m_shader_id);

    GLint is_valid{ 0 };
    glGetProgramiv(this->m_shader_id, GL_VALIDATE_STATUS, &is_valid);
    if (is_valid == GL_FALSE) {
        GLint max_length{ 0 };
        glGetProgramiv(this->m_shader_id, GL_INFO_LOG_LENGTH, &max_length);

        // The max_length includes the NULL character
        std::vector<GLchar> info_log(max_length);
        glGetProgramInfoLog(this->m_shader_id, max_length, &max_length, &info_log[0]);

        // Don't leak shaders either.
        glDeleteProgram(this->m_shader_id);

        // Use the info_log as you see fit.
        DUSK_CORE_ERROR(info_log.data());
        DUSK_CORE_ASSERT(false, "Program validation failed!");

        return;
    }
}
#endif

DUSK_NAMESPACE_END
