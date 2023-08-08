#ifndef _DUSK_UTILS_FOR_EACH_HPP_
#define _DUSK_UTILS_FOR_EACH_HPP_

#include <tuple>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

namespace ForEachDetail {

    template <typename Func, typename TupleType1, typename TupleType2, std::size_t... Index>
    void for_each_in_two_tuples_impl(Func&& f, TupleType1&& t1, TupleType2&& t2, std::index_sequence<Index...>) {
        (f(std::get<Index>(t1), std::get<Index>(t2)), ...);
    }

} // namespace ForEachDetail

/// @brief Applies a function to each element in a tuple.
/// Equivalent to: f(std::get<0>(t)), f(std::get<1>(t)), ...
template <typename Func, typename TupleType>
void for_each_in_tuple(Func&& f, TupleType&& t) {
    std::apply(
        [&](auto&&... args) {
            (f(std::forward<decltype(args)>(args)), ...);
        },
        std::forward<TupleType>(t)
    );
}

/// @brief Applies a function to each element in two tuples.
/// If not equal length, only first `n` elements are applied to `f`.
/// Equivalent to: f(std::get<0>(t1), std::get<0>(t2)), f(std::get<1>(t1), std::get<1>(t2)), ...
template <typename Func, typename TupleType1, typename TupleType2>
void for_each_in_two_tuples(Func&& f, TupleType1&& t1, TupleType2&& t2) {
    ForEachDetail::for_each_in_two_tuples_impl(
        std::forward<Func>(f),
        std::forward<TupleType1>(t1),
        std::forward<TupleType2>(t2),
        std::make_index_sequence<std::min(
            std::tuple_size_v<std::remove_reference_t<TupleType1>>,
            std::tuple_size_v<std::remove_reference_t<TupleType2>>
        )>{}
    );
}

DUSK_NAMESPACE_END

#endif // !_DUSK_UTILS_FOR_EACH_HPP_
