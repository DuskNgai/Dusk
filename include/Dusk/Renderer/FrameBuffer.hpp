#ifndef _DUSK_RENDERER_FRAME_BUFFER_HPP_
#define _DUSK_RENDERER_FRAME_BUFFER_HPP_

#include <memory>

#include <Dusk/Common.hpp>

DUSK_NAMESPACE_BEGIN

struct FrameBufferProps {
    uint32_t Width{0}, Height{0};
    uint32_t Samples{1};

    bool SwapChainTarget{false};
};

/// @class The offline rendering buffer.
class FrameBuffer {
public:
    virtual ~FrameBuffer() = default;

public:
    static std::shared_ptr<FrameBuffer> Create(FrameBufferProps const& props);

    /// @brief Bind the frame buffer.
    virtual void Bind() = 0;
    /// @brief Unbind the frame buffer.
    virtual void Unbind() = 0;

    /// @brief Get the color attachment related to the frame buffer.
    virtual uint32_t GetColorAttachment() = 0;

    /// @brief Resize the frame buffer.
    virtual void Resize(uint32_t width, uint32_t height) = 0;
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_FRAME_BUFFER_HPP_
