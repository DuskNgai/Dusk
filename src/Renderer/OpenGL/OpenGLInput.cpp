#include <Dusk/Core/Application/Application.hpp>
#include <Dusk/Renderer/Input.hpp>

#include <GLFW/glfw3.h>

DUSK_NAMESPACE_BEGIN

bool Input::IsKeyPressed(KeyCode key) {
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetWindowRawPtr());
    int state = glfwGetKey(window, static_cast<int>(key));
    return state == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(MouseCode button) {
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetWindowRawPtr());
    int state = glfwGetMouseButton(window, static_cast<int>(button));
    return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition() {
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetWindowRawPtr());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {static_cast<float>(xpos), static_cast<float>(ypos)};
}

float Input::GetMouseX() {
    return Input::GetMousePosition().x;
}

float Input::GetMouseY() {
    return Input::GetMousePosition().y;
}

DUSK_NAMESPACE_END
