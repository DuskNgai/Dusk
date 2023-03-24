#include <dusk/core/window/window.hpp>

DUSK_NAMESPACE_BEGIN

std::unique_ptr<WindowBase> WindowBase::create(WindowProps const& props) {
    return std::make_unique<Window>(props);
}

DUSK_NAMESPACE_END
