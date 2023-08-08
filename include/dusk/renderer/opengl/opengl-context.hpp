#ifndef _DUSK_RENDERER_OPENGL_OPENGL_CONTEXT_HPP_
#define _DUSK_RENDERER_OPENGL_OPENGL_CONTEXT_HPP_

#include <GLFW/glfw3.h>

#include <dusk/renderer/graphics-context.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief OpenGLContext contains opengl rendering context.
class OpenGLContext : public GraphicsContext {
private:
    GLFWwindow* m_window;

public:
    OpenGLContext(GLFWwindow* window);
    virtual ~OpenGLContext() override = default;

public:
    virtual void swap_buffers() override;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_OPENGL_OPENGL_CONTEXT_HPP_
