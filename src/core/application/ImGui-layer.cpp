#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <dusk/core/application/ImGui-layer.hpp>
#include <dusk/core/application/application.hpp>
#include <dusk/core/utils/utils.hpp>

DUSK_NAMESPACE_BEGIN

ImGuiLayer::ImGuiLayer()
    : Layer{ "ImGuiLayer" } {}

void ImGuiLayer::on_attach() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport

    // Setup Dear ImGui style
    ImGui::StyleColorsClassic();

    GLFWwindow* window{ static_cast<GLFWwindow*>(Application::get()->get_window()->get_window_raw_ptr()) };

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Scaling the ImGui window size
    float x_scale, y_scale;
    glfwGetWindowContentScale(window, &x_scale, &y_scale);
    if (x_scale > 1.0f) {
        ImGui::GetStyle().ScaleAllSizes(x_scale);
        io.Fonts->AddFontFromFileTTF(get_file_path("assets/fonts/SourceCodePro.ttf").c_str(), 15.0f * x_scale);
    }
    else {
        io.Fonts->AddFontFromFileTTF(get_file_path("assets/fonts/SourceCodePro.ttf").c_str(), 20.0f);
    }
}

void ImGuiLayer::on_detach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::begin_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::end_frame() {
    // Rendering
    ImGuiIO& io{ ImGui::GetIO() };
    Application* app{ Application::get() };
    io.DisplaySize = ImVec2(
        static_cast<float>(app->get_window()->get_width()),
        static_cast<float>(app->get_window()->get_height())
    );

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context{ glfwGetCurrentContext() };
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void ImGuiLayer::on_event(EventBase& e) {
    if (this->m_block_event) {
        ImGuiIO& io = ImGui::GetIO();
        e.m_handled |= e.is_in_category(EventCategoryMouse) & io.WantCaptureMouse;
        e.m_handled |= e.is_in_category(EventCategoryKeyboard) & io.WantCaptureKeyboard;
    }
}

void ImGuiLayer::set_block_event(bool is_block) { this->m_block_event = is_block; }

DUSK_NAMESPACE_END
