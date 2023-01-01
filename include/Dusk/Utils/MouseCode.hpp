#ifndef _DUSK_MOUSE_CODE_HPP_
#define _DUSK_MOUSE_CODE_HPP_

#include <Dusk/Common.hpp>

DUSK_NAMESPACE_BEGIN

// From glfw3.h mouse code mapping.
// clang-format off
enum class MouseCode : uint16_t {
    Button0                = 0,
    Button1                = 1,
    Button2                = 2,
    Button3                = 3,
    Button4                = 4,
    Button5                = 5,
    Button6                = 6,
    Button7                = 7,

    ButtonLast             = Button7,
    ButtonLeft             = Button0,
    ButtonRight            = Button1,
    ButtonMiddle           = Button2
};
// clang-format on

DUSK_NAMESPACE_END

#endif // !_DUSK_MOUSE_CODE_HPP_
