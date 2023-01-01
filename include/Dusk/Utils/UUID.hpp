#ifndef _DUSK_UTILS_UUID_H_
#define _DUSK_UTILS_UUID_H_

#include <cstdint>
#include <random>

#include <Dusk/Common.hpp>

DUSK_NAMESPACE_BEGIN

class UUID {
private:
    uint64_t m_uuid;

public:
    UUID();
    UUID(uint64_t uuid);
    UUID(UUID const& other) = default;

    operator uint64_t() const;
};

DUSK_NAMESPACE_END

namespace std {
    template <typename T>
    struct hash;

    template <>
    struct hash<Dusk::UUID> {
        std::size_t operator()(Dusk::UUID const& uuid) const {
            return static_cast<std::size_t>(uuid);
        }
    };
} // namespace std

#endif // !_DUSK_UTILS_UUID_H_
