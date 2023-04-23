#ifndef _DUSK_RENDERER_FRAME_BUFFER_HPP_
#define _DUSK_RENDERER_FRAME_BUFFER_HPP_

#include <memory>

#include <glm/glm.hpp>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

struct FramebufferProps {
    glm::uvec2 Size{ 0, 0 };
    uint32_t Samples{ 1 };

    bool SwapChainTarget{ false };
};

/// @class The offline rendering buffer.
class Framebuffer {
public:
    virtual ~Framebuffer() = default;

public:
    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual uint32_t get_color_attachment() = 0;

    virtual void resize(glm::uvec2 new_size) = 0;
    virtual void resize(uint32_t width, uint32_t height) = 0;

    static std::unique_ptr<Framebuffer> create(FramebufferProps const& props);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_FRAME_BUFFER_HPP_
