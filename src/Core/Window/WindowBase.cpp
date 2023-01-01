#include <Dusk/Core/Window/Window.hpp>

DUSK_NAMESPACE_BEGIN

std::unique_ptr<WindowBase> WindowBase::Create(WindowProps const& props) {
    return std::make_unique<Window>(props);
}

DUSK_NAMESPACE_END
