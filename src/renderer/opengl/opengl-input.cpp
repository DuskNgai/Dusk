#include <dusk/core/application/application.hpp>
#include <dusk/renderer/input.hpp>

#include <GLFW/glfw3.h>

DUSK_NAMESPACE_BEGIN

bool Input::is_key_pressed(KeyCode key) {
    GLFWwindow* window{ static_cast<GLFWwindow*>(Application::get()->get_window()->get_window_raw_ptr()) };
    int state{ glfwGetKey(window, static_cast<int>(key)) };
    return state == GLFW_PRESS;
}

bool Input::is_mouse_button_pressed(MouseCode button) {
    GLFWwindow* window{ static_cast<GLFWwindow*>(Application::get()->get_window()->get_window_raw_ptr()) };
    int state{ glfwGetMouseButton(window, static_cast<int>(button)) };
    return state == GLFW_PRESS;
}

glm::vec2 Input::get_mouse_position() {
    GLFWwindow* window{ static_cast<GLFWwindow*>(Application::get()->get_window()->get_window_raw_ptr()) };
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return { static_cast<float>(xpos), static_cast<float>(ypos) };
}

float Input::get_mouse_x() {
    return Input::get_mouse_position().x;
}

float Input::get_mouse_y() {
    return Input::get_mouse_position().y;
}

DUSK_NAMESPACE_END
