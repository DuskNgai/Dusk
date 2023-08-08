#ifndef _DUSK_UTILS_UUID_HPP_
#define _DUSK_UTILS_UUID_HPP_

#include <cstdint>

#include <dusk/common.hpp>

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
    struct hash<dusk::UUID> {
        std::size_t operator()(dusk::UUID const& uuid) const {
            return static_cast<std::size_t>(uuid);
        }
    };
} // namespace std

#endif // !_DUSK_UTILS_UUID_HPP_
