#include <Dusk/Assert.hpp>
#include <Dusk/Log.hpp>
#include <Dusk/Core/Application/Application.hpp>
#include <Dusk/Renderer/Renderer.hpp>
#include <Dusk/Utils/Timer.hpp>

#include <GLFW/glfw3.h>

DUSK_NAMESPACE_BEGIN

Application* Application::s_instance = nullptr;

Application::Application()
    : m_window{WindowBase::Create()} {
    DUSK_CORE_ASSERT(Application::s_instance == nullptr, "Application already exists!");
    Application::s_instance = this;

    this->GetWindow()->SetEventCallback(DUSK_BIND_CLASS_FN(Application::OnEvent));

    Renderer::Init();

    this->m_imgui_layer = new ImGuiLayer();
    this->PushOverlay(this->m_imgui_layer);
}

Application::~Application() {
    Application::s_instance = nullptr;

    Renderer::Shutdown();
}

void Application::PushLayer(Layer* layer) {
    this->m_layer_stack.PushLayer(layer);
    layer->OnAttach();
    this->m_is_running = true;
}

void Application::PushOverlay(Layer* layer) {
    this->m_layer_stack.PushOverlay(layer);
    layer->OnAttach();
}

void Application::PopLayer(Layer* layer) {
    layer->OnDetach();
    this->m_layer_stack.PopLayer(layer);
}

void Application::PopOverlay(Layer* layer) {
    layer->OnDetach();
    this->m_layer_stack.PopOverlay(layer);
}

void Application::Run() {
    while (this->m_is_running) {
        // Timer
        Timer::UpdateDeltaTime();

        // Rendering forward.
        // That is, the layer that is on the top of the layerstack will be rendered first and at the bottom of the window.
        for (auto&& layer : this->m_layer_stack) {
            layer->OnUpdate();
        }

        // ImGui stuffs.
        this->m_imgui_layer->Begin();
        for (auto&& layer : this->m_layer_stack) {
            layer->OnImGuiRender();
        }
        this->m_imgui_layer->End();

        this->GetWindow()->OnUpdate();
    }
}

void Application::OnEvent(EventBase& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(DUSK_BIND_CLASS_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(DUSK_BIND_CLASS_FN(Application::OnWindowResize));
    dispatcher.Dispatch<KeyPressedEvent>(DUSK_BIND_CLASS_FN(Application::OnKeyPressed));

    // Dealing with events backward.
    // That is, the layer that is rendered at the top of the window receives the event first.
    for (auto it = this->m_layer_stack.rbegin(); it != this->m_layer_stack.rend(); ++it) {
        if (e.m_handled) {
            break;
        }
        (*it)->OnEvent(e);
    }
}

Application* Application::Get() { return Application::s_instance; }

WindowBase* Application::GetWindow() { return this->m_window.get(); }

bool Application::OnWindowClose([[maybe_unused]] WindowCloseEvent& e) {
    this->m_is_running = false;
    return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e) {
    RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
    return false;
}

bool Application::OnKeyPressed(KeyPressedEvent& e) {
    if (e.GetKeyCode() == KeyCode::Escape) {
        this->m_is_running = false;
        return true;
    }
    return false;
}

DUSK_NAMESPACE_END
