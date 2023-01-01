#ifndef _DUSK_UTILS_UTILS_HPP_
#define _DUSK_UTILS_UTILS_HPP_

#include <array>
#include <filesystem>

#include <Dusk/Common.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief Find the `target` file from current working directory up to specified `depth`.
std::string GetFilePath(std::string const& target, int depth = 5);

/// @brief Read all the texts in the given `filename`.
std::string ReadTextFile(std::string const& filename);

/// @brief Convert integer sequence to std::array (before C++20).
template <typename T, T... N>
constexpr std::array<T, sizeof...(N)> IntegerSequenceToArray(std::integer_sequence<T, N...>) {
    return {N...};
}

DUSK_NAMESPACE_END

#endif // !_DUSK_UTILS_UTILS_HPP_
