#include <Dusk/Renderer/OpenGL/OpenGLContext.hpp>

DUSK_NAMESPACE_BEGIN

std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window) {
    return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
}

DUSK_NAMESPACE_END
