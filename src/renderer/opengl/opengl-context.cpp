#include <fmt/core.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <dusk/assert.hpp>
#include <dusk/log.hpp>
#include <dusk/renderer/opengl/opengl-context.hpp>

DUSK_NAMESPACE_BEGIN

OpenGLContext::OpenGLContext(GLFWwindow* window)
    : m_window{ window } {
    DUSK_CORE_ASSERT(window, "Window is nullptr!");

    glfwMakeContextCurrent(this->m_window);

    auto version{ gladLoadGL(glfwGetProcAddress) };
    DUSK_CORE_INFO("OpenGL Version: {:d}.{:d}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    auto u8_to_i8{ [](GLenum item) {
        return fmt::format("{:s}", reinterpret_cast<char const*>(glGetString(item)));
    } };
    DUSK_CORE_INFO("OpenGL Info:");
    DUSK_CORE_INFO("\tVendor: {:s}", u8_to_i8(GL_VENDOR));
    DUSK_CORE_INFO("\tRenderer: {:s}", u8_to_i8(GL_RENDERER));
    DUSK_CORE_INFO("\tVersion: {:s}", u8_to_i8(GL_VERSION));
    DUSK_CORE_INFO("\tGLSL Version: {:s}", u8_to_i8(GL_SHADING_LANGUAGE_VERSION));
}

void OpenGLContext::swap_buffers() {
    glfwSwapBuffers(this->m_window);
}

DUSK_NAMESPACE_END
