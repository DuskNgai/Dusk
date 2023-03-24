#ifndef _DUSK_UTILS_UTILS_HPP_
#define _DUSK_UTILS_UTILS_HPP_

#include <array>
#include <filesystem>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

/// @brief Find the `target` file from current working directory up to specified `depth`.
/// @param target The target file name.
/// @param depth The depth of the search.
/// @return The path of the target file.
std::string get_file_path(std::string const& target, int depth = 5);

/// @brief Read all the texts in the given `file_name`.
/// @param file_name The file name.
/// @return The text content of the file.
std::string read_text_file(std::string const& file_name);

/// @brief Convert integer sequence to std::array (before C++20).
template <typename T, T... N>
constexpr std::array<T, sizeof...(N)> IntegerSequenceToArray(std::integer_sequence<T, N...>) {
    return { N... };
}

DUSK_NAMESPACE_END

#endif // !_DUSK_UTILS_UTILS_HPP_
