#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Dusk/Core/Application/ImGuiLayer.hpp>
#include <Dusk/Core/Application/Application.hpp>
#include <Dusk/Utils/Utils.hpp>

DUSK_NAMESPACE_BEGIN

ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer") {}

void ImGuiLayer::OnAttach() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport

    // Setup Dear ImGui style
    ImGui::StyleColorsClassic();

    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetWindowRawPtr());

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Scaling the ImGui window size
    float x_scale, y_scale;
    glfwGetWindowContentScale(window, &x_scale, &y_scale);
    if (x_scale > 1.0f) {
        ImGui::GetStyle().ScaleAllSizes(x_scale);
        io.Fonts->AddFontFromFileTTF(GetFilePath("assets/fonts/SourceCodePro.ttf").c_str(), 15.0f * x_scale);
    }
    else {
        io.Fonts->AddFontFromFileTTF(GetFilePath("assets/fonts/SourceCodePro.ttf").c_str(), 20.0f);
    }
}

void ImGuiLayer::OnDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::End() {
    // Rendering
    ImGuiIO& io = ImGui::GetIO();
    Application* app = Application::Get();
    io.DisplaySize = ImVec2(
        static_cast<float>(app->GetWindow()->GetWidth()),
        static_cast<float>(app->GetWindow()->GetHeight())
    );

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void ImGuiLayer::OnEvent(EventBase& e) {
    if (m_block_event) {
        ImGuiIO& io = ImGui::GetIO();
        e.m_handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
        e.m_handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
    }
}

void ImGuiLayer::BlockEvent(bool block) { this->m_block_event = block; }

DUSK_NAMESPACE_END
