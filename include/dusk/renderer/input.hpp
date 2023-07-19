#ifndef _DUSK_RENDERER_INPUT_HPP_
#define _DUSK_RENDERER_INPUT_HPP_

#include <glm/glm.hpp>

#include <dusk/utils/key-code.hpp>
#include <dusk/utils/mouse-code.hpp>

DUSK_NAMESPACE_BEGIN

/// @class: Singleton mode of encapsuled input system.
class Input {
public:
    static bool is_key_pressed(KeyCode key);

    static bool is_mouse_button_pressed(MouseCode button);

    static glm::vec2 get_mouse_position();
    static float get_mouse_x();
    static float get_mouse_y();
};

DUSK_NAMESPACE_END

#endif // !_DUSK_RENDERER_INPUT_HPP_
