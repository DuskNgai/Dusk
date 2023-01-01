#ifndef _DUSK_COMMON_HPP_
#define _DUSK_COMMON_HPP_

#define DUSK_NAMESPACE_BEGIN namespace Dusk {
#define DUSK_NAMESPACE_END }

#define DUSK_BIND_CLASS_FN(fn) [this](auto&&... args) -> decltype(auto) { \
    return this->fn(std::forward<decltype(args)>(args)...);               \
}

#endif // !_DUSK_COMMON_HPP_
