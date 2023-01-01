#ifndef _DUSK_RENDERER_INPUT_HPP_
#define _DUSK_RENDERER_INPUT_HPP_

#include <glm/glm.hpp>

#include <Dusk/Utils/KeyCode.hpp>
#include <Dusk/Utils/MouseCode.hpp>

DUSK_NAMESPACE_BEGIN

/// @class: Singleton mode of encapsuled input system.
class Input {
public:
    /// @brief Check if the desired `key` is pressed.
    static bool IsKeyPressed(KeyCode key);

    /// @brief Check if the desired `button` is pressed.
    static bool IsMouseButtonPressed(MouseCode button);

    static glm::vec2 GetMousePosition();
    static float GetMouseX();
    static float GetMouseY();
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_INPUT_HPP_
