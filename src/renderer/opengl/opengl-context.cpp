#include <dusk/platform-detection.hpp>
#if defined(DUSK_PLATFORM_WINDOWS)
    #include <windows.h>
#endif

#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <dusk/assert.hpp>
#include <dusk/log.hpp>
#include <dusk/renderer/opengl/opengl-context.hpp>

DUSK_NAMESPACE_BEGIN

OpenGLContext::OpenGLContext(GLFWwindow* window)
    : m_window{ window } {
    DUSK_CORE_ASSERT(window, "Window is nullptr!");
}

void OpenGLContext::init() {
    glfwMakeContextCurrent(this->m_window);
    auto status{ gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
    DUSK_CORE_ASSERT(status, "Failed to initialize Glad!");

    auto u8_to_i8 = [](int item) {
        std::stringstream ss;
        ss << glGetString(item);
        return ss.str();
    };
    DUSK_CORE_INFO("OpenGL Info:");
    DUSK_CORE_INFO("Vendor: {:s}", u8_to_i8(GL_VENDOR));
    DUSK_CORE_INFO("Renderer: {:s}", u8_to_i8(GL_RENDERER));
    DUSK_CORE_INFO("Version: {:s}", u8_to_i8(GL_VERSION));
}

void OpenGLContext::swap_buffers() {
    glfwSwapBuffers(this->m_window);
}

DUSK_NAMESPACE_END
