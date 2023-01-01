#include <vector>

#include <Dusk/Assert.hpp>
#include <Dusk/Log.hpp>
#include <Dusk/Renderer/OpenGL/OpenGLShader.hpp>

DUSK_NAMESPACE_BEGIN

OpenGLShader::OpenGLShader(std::string const& vs, std::string const& fs) {
    GLuint vertex_shader = this->CompileShader(vs, GL_VERTEX_SHADER);
    GLuint fragment_shader = this->CompileShader(fs, GL_FRAGMENT_SHADER);

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    this->m_shader_id = glCreateProgram();
    this->LinkShader(vertex_shader, fragment_shader);
#ifndef NDEBUG
    this->ValidateShader();
#endif
}

OpenGLShader::~OpenGLShader() {
    glDeleteProgram(this->m_shader_id);
}

void OpenGLShader::Bind() const {
    glUseProgram(this->m_shader_id);
}

void OpenGLShader::Unbind() const {
    glUseProgram(0);
}

void OpenGLShader::SetInt(std::string const& name, int val) const {
    auto location = this->GetUniformLocation(name);
    glUniform1i(location, val);
}

void OpenGLShader::SetIntArray(std::string const& name, int* vals, uint32_t count) const {
    auto location = this->GetUniformLocation(name);
    glUniform1iv(location, count, vals);
}

void OpenGLShader::SetFloat(std::string const& name, float val) const {
    auto location = this->GetUniformLocation(name);
    glUniform1f(location, val);
}

void OpenGLShader::SetVec2(std::string const& name, glm::vec2 const& val) const {
    auto location = this->GetUniformLocation(name);
    glUniform2f(location, val.x, val.y);
}

void OpenGLShader::SetVec3(std::string const& name, glm::vec3 const& val) const {
    auto location = this->GetUniformLocation(name);
    glUniform3f(location, val.x, val.y, val.z);
}

void OpenGLShader::SetVec4(std::string const& name, glm::vec4 const& val) const {
    auto location = this->GetUniformLocation(name);
    glUniform4f(location, val.x, val.y, val.z, val.w);
}

void OpenGLShader::SetMat2(std::string const& name, glm::mat2 const& val) const {
    auto location = this->GetUniformLocation(name);
    glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

void OpenGLShader::SetMat3(std::string const& name, glm::mat3 const& val) const {
    auto location = this->GetUniformLocation(name);
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

void OpenGLShader::SetMat4(std::string const& name, glm::mat4 const& val) const {
    auto location = this->GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

GLint OpenGLShader::GetUniformLocation(std::string const& name) const {
    // Cache it if not find.
    if (this->m_uniform_cache.find(name) == this->m_uniform_cache.end()) {
        this->m_uniform_cache[name] = glGetUniformLocation(this->m_shader_id, name.c_str());
    }
    return this->m_uniform_cache[name];
}

GLuint OpenGLShader::CompileShader(std::string const& code, GLenum shader_type) const {
    // An vertex shader handle
    GLuint shader = glCreateShader(shader_type);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    GLchar const* source = code.c_str();
    glShaderSource(shader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(shader);

    GLint is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE) {
        GLint max_length = 0;
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

void OpenGLShader::LinkShader(GLuint vertex_shader, GLuint fragment_shader) const {
    // Attach our shaders to our program
    glAttachShader(this->m_shader_id, vertex_shader);
    glAttachShader(this->m_shader_id, fragment_shader);

    // Link our program
    glLinkProgram(this->m_shader_id);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(this->m_shader_id, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint max_length = 0;
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
void OpenGLShader::ValidateShader() const {
    GLint is_valid = 0;
    glGetProgramiv(this->m_shader_id, GL_VALIDATE_STATUS, &is_valid);
    if (is_valid == GL_FALSE) {
        GLint max_length = 0;
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
