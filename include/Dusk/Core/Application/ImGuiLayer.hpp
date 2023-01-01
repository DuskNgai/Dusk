#ifndef _DUSK_CORE_APPLICATION_IMGUI_LAYER_HPP_
#define _DUSK_CORE_APPLICATION_IMGUI_LAYER_HPP_

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <Dusk/Core/Application/Layer.hpp>

DUSK_NAMESPACE_BEGIN

/// @class A special layer for only dealing with the events related to ImGui.
/// @see Layer
class ImGuiLayer : public Layer {
private:
    bool m_block_event{true};

public:
    ImGuiLayer();
    virtual ~ImGuiLayer() override = default;

public:
    virtual void OnAttach() override;

    virtual void OnDetach() override;

    /// @brief `OnUpdate` is broken into three parts.
    /// This part contains several operations at the beginning of the new frame.
    void Begin();

    /// @brief `OnUpdate` is broken into three parts.
    /// This part contains several operations at the end of the frame.
    void End();

    virtual void OnEvent(EventBase& e) override;

    void BlockEvent(bool block);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_APPLICATION_IMGUI_LAYER_HPP_
