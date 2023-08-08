#include <dusk/core/application/layer.hpp>

DUSK_NAMESPACE_BEGIN

Layer::Layer(std::string const& name)
    : m_debug_name{ name } {}

std::string const& Layer::get_name() const { return this->m_debug_name; }

DUSK_NAMESPACE_END
