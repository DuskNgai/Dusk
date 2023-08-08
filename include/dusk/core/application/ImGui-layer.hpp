#ifndef _DUSK_CORE_APPLICATION_IMGUI_LAYER_HPP_
#define _DUSK_CORE_APPLICATION_IMGUI_LAYER_HPP_

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <dusk/core/application/layer.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief A special layer for only dealing with the events related to ImGui.
/// @see Layer
class ImGuiLayer : public Layer {
private:
    bool m_block_event{ true };

public:
    ImGuiLayer();
    virtual ~ImGuiLayer() override = default;

public:
    virtual void on_attach() override;

    virtual void on_detach() override;

    virtual void on_update() override;

    virtual void on_ImGui_render() override;

    /// @brief Dispatch the event to this ImGui layer.
    virtual void on_event(EventBase& e) override;

    /// @brief Each frame call this function to start a new ImGui frame.
    void begin_frame();

    /// @brief Each frame call this function to end the current ImGui frame.
    void end_frame();

    bool is_block_event() const;

    void set_block_event(bool is_block);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_APPLICATION_IMGUI_LAYER_HPP_
