#ifndef _DUSK_CORE_WINDOW_WINDOW_PROPS_HPP_
#define _DUSK_CORE_WINDOW_WINDOW_PROPS_HPP_

#include <string>

#include "dusk/common.hpp"

DUSK_NAMESPACE_BEGIN

struct WindowProps {
    uint32_t m_width{ 1920 };
    uint32_t m_height{ 1080 };
    std::string m_title{ "Dusk-Engine" };
};

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_WINDOW_WINDOW_PROPS_HPP_
