#include <Dusk/Core/Application/Layer.hpp>

DUSK_NAMESPACE_BEGIN

Layer::Layer(std::string const& name)
    : m_debug_name{name} {}

std::string const& Layer::GetName() const { return this->m_debug_name; }

void Layer::OnAttach() {}
void Layer::OnDetach() {}
void Layer::OnUpdate() {}
void Layer::OnImGuiRender() {}
void Layer::OnEvent([[maybe_unused]] EventBase& e) {}

DUSK_NAMESPACE_END
