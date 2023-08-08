#include <dusk/assert.hpp>
#include <dusk/log.hpp>
#include <dusk/core/application/application.hpp>
#include <dusk/core/event/event-dispatcher.hpp>
#include <dusk/utils/timer.hpp>
#include <dusk/renderer/renderer.hpp>

#include <GLFW/glfw3.h>

DUSK_NAMESPACE_BEGIN

Application* Application::s_instance{ nullptr };

Application::Application() {
    // Singleton mode.
    DUSK_CORE_ASSERT(Application::s_instance == nullptr, "Application already exists!");
    Application::s_instance = this;

    // Create the main window and bind the callbacks.
    this->m_window = WindowBase::create();
    this->get_window()->set_event_callback(DUSK_BIND_CLASS_FN(Application::on_event));

    Renderer::initialize();

    this->m_imgui_layer = new ImGuiLayer();
    this->push_overlay(this->m_imgui_layer);
}

Application::~Application() {
    Renderer::terminate();
}

void Application::push_layer(Layer* layer) {
    this->m_layer_stack.push_layer(layer);
}

void Application::push_overlay(Layer* layer) {
    this->m_layer_stack.push_overlay(layer);
}

void Application::pop_layer(Layer* layer) {
    this->m_layer_stack.pop_layer(layer);
}

void Application::pop_overlay(Layer* layer) {
    this->m_layer_stack.pop_overlay(layer);
}

void Application::run() {
    while (this->m_is_running) {
        // Using timer to manage the time step between each frame.
        Timer::update_delta_time();

        // Rendering forward.
        // The layer on the top of the layerstack will be rendered first and at the bottom of the window.
        for (auto&& layer : this->m_layer_stack) {
            layer->on_update();
        }

        // ImGui stuffs.
        this->m_imgui_layer->begin_frame();
        for (auto&& layer : this->m_layer_stack) {
            layer->on_ImGui_render();
        }
        this->m_imgui_layer->end_frame();

        this->get_window()->on_update();
    }
}

void Application::on_event(EventBase& e) {
    // Dealing with events backward.
    // That is, the layer that is rendered at the top of the window receives the event first.
    for (auto it{ this->m_layer_stack.rbegin() }; it != this->m_layer_stack.rend(); ++it) {
        if (e.is_handled()) {
            break;
        }
        (*it)->on_event(e);
    }

    // The window is at the bottom of the layerstack.
    if (not e.is_handled()) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(DUSK_BIND_CLASS_FN(Application::on_window_close));
        dispatcher.dispatch<WindowResizeEvent>(DUSK_BIND_CLASS_FN(Application::on_window_resize));
        dispatcher.dispatch<KeyPressedEvent>(DUSK_BIND_CLASS_FN(Application::on_key_pressed));
    }
}

Application* Application::get() { return Application::s_instance; }

WindowBase* Application::get_window() { return this->m_window.get(); }

ImGuiLayer* Application::get_imgui_layer() { return this->m_imgui_layer; }

bool Application::on_window_close([[maybe_unused]] WindowCloseEvent& e) {
    this->m_is_running = false;
    return true;
}

bool Application::on_window_resize(WindowResizeEvent& e) {
    RenderCommand::set_viewport(0, 0, e.get_width(), e.get_height());
    return false;
}

bool Application::on_key_pressed(KeyPressedEvent& e) {
    if (e.get_key_code() == KeyCode::Escape) {
        this->m_is_running = false;
        return true;
    }
    return false;
}

DUSK_NAMESPACE_END
