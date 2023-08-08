#ifndef _DUSK_RENDERER_GRAPHICS_CONTEXT_HPP_
#define _DUSK_RENDERER_GRAPHICS_CONTEXT_HPP_

#include <memory>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

class GraphicsContext {
public:
    virtual ~GraphicsContext() = default;

public:
    virtual void swap_buffers() = 0;

    static std::unique_ptr<GraphicsContext> create(void* window);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_GRAPHICS_CONTEXT_HPP_
