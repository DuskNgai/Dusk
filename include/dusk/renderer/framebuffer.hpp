#ifndef _DUSK_RENDERER_FRAME_BUFFER_HPP_
#define _DUSK_RENDERER_FRAME_BUFFER_HPP_

#include <memory>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

struct FramebufferProps {
    uint32_t Width{ 0 }, Height{ 0 };
    uint32_t Samples{ 1 };

    bool SwapChainTarget{ false };
};

/// @class The offline rendering buffer.
class Framebuffer {
public:
    virtual ~Framebuffer() = default;

public:
    /// @brief Bind the frame buffer.
    virtual void bind() = 0;
    /// @brief Unbind the frame buffer.
    virtual void unbind() = 0;

    /// @brief Get the color attachment related to the frame buffer.
    virtual uint32_t get_color_attachment() = 0;

    /// @brief Resize the frame buffer.
    virtual void resize(uint32_t width, uint32_t height) = 0;

    /// @brief Create a frame buffer based on the given properties.
    static std::shared_ptr<Framebuffer> create(FramebufferProps const& props);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_FRAME_BUFFER_HPP_
