#ifndef _DUSK_RENDERER_OPENGL_CONTEXT_HPP_
#define _DUSK_RENDERER_OPENGL_CONTEXT_HPP_

#include <GLFW/glfw3.h>

#include <Dusk/Renderer/GraphicsContext.hpp>

DUSK_NAMESPACE_BEGIN

/// @class OpenGLContext contains opengl rendering context.
/// @see GraphicsContext
class OpenGLContext : public GraphicsContext {
private:
    GLFWwindow* m_window;

public:
    OpenGLContext(GLFWwindow* window);

public:
    virtual void Init() override;
    virtual void SwapBuffers() override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_CONTEXT_HPP_
