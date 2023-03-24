#include <dusk/core/application/layer.hpp>

DUSK_NAMESPACE_BEGIN

Layer::Layer(std::string const& name)
    : m_debug_name{ name } {}

std::string const& Layer::get_name() const { return this->m_debug_name; }

void Layer::on_attach() {}
void Layer::on_detach() {}
void Layer::on_update() {}
void Layer::on_ImGui_render() {}
void Layer::on_event([[maybe_unused]] EventBase& e) {}

DUSK_NAMESPACE_END
