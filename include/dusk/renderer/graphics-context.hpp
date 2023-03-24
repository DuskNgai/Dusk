#ifndef _DUSK_RENDERER_GRAPHCIS_CONTEXT_HPP_
#define _DUSK_RENDERER_GRAPHCIS_CONTEXT_HPP_

#include <memory>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

class GraphicsContext {
public:
    virtual ~GraphicsContext() = default;

public:
    /// @brief Initialization of the window.
    virtual void init() = 0;

    /// @brief Swap the rendering buffers.
    virtual void swap_buffers() = 0;

    /// @brief Connect to a proper rendering API.
    static std::unique_ptr<GraphicsContext> create(void* window);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_GRAPHCIS_CONTEXT_HPP_
