#ifndef _DUSK_COMMON_HPP_
#define _DUSK_COMMON_HPP_

// clang-format off
#define DUSK_NAMESPACE_BEGIN namespace dusk {
#define DUSK_NAMESPACE_END                  }
// clang-format on

#define DUSK_BIND_CLASS_FN(fn) [this](auto&&... args) -> decltype(auto) { \
    return this->fn(std::forward<decltype(args)>(args)...);               \
}

#endif // !_DUSK_COMMON_HPP_
