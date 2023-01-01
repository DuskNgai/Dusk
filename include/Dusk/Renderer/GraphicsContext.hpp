#ifndef _DUSK_RENDERER_GRAPHCIS_CONTEXT_HPP_
#define _DUSK_RENDERER_GRAPHCIS_CONTEXT_HPP_

#include <memory>

#include <Dusk/Common.hpp>

DUSK_NAMESPACE_BEGIN

class GraphicsContext {
public:
    virtual ~GraphicsContext() = default;

public:
    /// @brief Connect to a proper rendering API.
    static std::unique_ptr<GraphicsContext> Create(void* window);

    /// @brief Initialization of the window.
    virtual void Init() = 0;

    /// @brief Swap the rendering buffers.
    virtual void SwapBuffers() = 0;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_GRAPHCIS_CONTEXT_HPP_
