#include <Dusk/Utils/UUID.hpp>

DUSK_NAMESPACE_BEGIN

static std::random_device s_rd;
static std::mt19937_64 s_rng(s_rd());
static std::uniform_int_distribution<uint64_t> s_unif_uint64;

UUID::UUID()
    : m_uuid{s_unif_uint64(s_rng)} {}

UUID::UUID(uint64_t uuid)
    : m_uuid{uuid} {}

UUID::operator uint64_t() const { return this->m_uuid; }

DUSK_NAMESPACE_END
