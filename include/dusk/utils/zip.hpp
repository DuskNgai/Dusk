#ifndef _DUSK_CORE_UTILS_ZIP_HPP_
#define _DUSK_CORE_UTILS_ZIP_HPP_

#include <tuple>
#include <type_traits>

#include <dusk/common.hpp>
#include <dusk/utils/for-each.hpp>

DUSK_NAMESPACE_BEGIN

namespace ZipperDetail {
    template <typename T>
    struct get_iterator {
        // `std::remove_reference_t<T>::iterator` is equivalent to `decltype(std::begin(std::declval<std::remove_reference_t<T>>()))`
        using type = decltype(std::begin(std::declval<std::remove_reference_t<T>>()));
    };

    template <typename T>
    using get_iterator_t = typename get_iterator<T>::type;

    template <typename T>
    struct iterator_tool;

    /// @tparam Types Containers.
    template <typename... Types>
    struct iterator_tool<std::tuple<Types...>> {
        using iterators = std::tuple<get_iterator_t<Types>...>;
        using value_type = std::tuple<typename std::remove_reference_t<Types>::value_type...>;
        using reference = std::tuple<typename std::remove_reference_t<Types>::reference...>;
        using pointer = std::tuple<typename std::remove_reference_t<Types>::pointer...>;
    };

    template <typename... Types, std::size_t... Index>
    auto get_ref_impl(std::tuple<Types...> const& t, std::index_sequence<Index...>) {
        return std::forward_as_tuple(*(std::get<Index>(t))...);
    }

    template <typename... Types>
    auto get_ref(std::tuple<Types...> const& t) {
        return get_ref_impl(t, std::index_sequence_for<Types...>{});
    }

    /// @brief Iterator of Zipper.
    /// @tparam TupleOfIterables A tuple of containers.
    template <typename TupleOfIterables>
    struct ZipperIterator {
    public:
        // Put the iterators of all the iterables in the tuple together as a whole iterator type.
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = typename iterator_tool<TupleOfIterables>::value_type;
        using reference = typename iterator_tool<TupleOfIterables>::reference;
        using pointer = typename iterator_tool<TupleOfIterables>::pointer;
        // TODO
        using iterator_category = std::bidirectional_iterator_tag;

        using Iterators = typename iterator_tool<TupleOfIterables>::iterators;

    public:
        Iterators iterators;

    public:
        ZipperIterator() = default;
        // It should make a copy, we can not modify the passed iterators.
        ZipperIterator(Iterators iterators)
            : iterators{ iterators } {}

    public:
        auto operator*() const { return get_ref(this->iterators); }
        // No actual meanings for `operator->()`.

        ZipperIterator& operator++() {
            for_each_in_tuple(
                [](auto& it) {
                    ++it;
                },
                this->iterators
            );
            return *this;
        }
        ZipperIterator operator++(int) {
            auto it{ *this };
            ++(*this);
            return it;
        }
        ZipperIterator& operator--() {
            for_each_in_tuple(
                [](auto& it) {
                    --it;
                },
                this->iterators
            );
            return *this;
        }
        ZipperIterator operator--(int) {
            auto it{ *this };
            --(*this);
            return it;
        }

        // Two iterator are equal if they have one corresponding element.
        bool operator==(ZipperIterator const& rhs) const {
            bool is_equal = false;
            for_each_in_two_tuples(
                [&](auto& it1, auto& it2) {
                    is_equal |= (it1 == it2);
                },
                this->iterators, rhs.iterators
            );
            return is_equal;
        }
        // Two iterator are not equal if they have one corresponding element.
        bool operator!=(ZipperIterator const& rhs) const {
            bool is_not_equal = true;
            for_each_in_two_tuples(
                [&](auto& it1, auto& it2) {
                    is_not_equal &= (it1 != it2);
                },
                this->iterators, rhs.iterators
            );
            return is_not_equal;
        }
    };

    template <typename TupleType, std::size_t... Index>
    auto get_begin_impl(TupleType& t, std::index_sequence<Index...>) {
        return std::make_tuple(std::begin(std::get<Index>(t))...);
    }

    template <typename... Types>
    auto get_begin(std::tuple<Types...>& t) {
        return get_begin_impl(t, std::index_sequence_for<Types...>{});
    }

    template <typename... Types>
    auto get_begin(std::tuple<Types...> const& t) {
        return get_begin_impl(t, std::index_sequence_for<Types...>{});
    }

    template <typename TupleType, std::size_t... Index>
    auto get_end_impl(TupleType& t, std::index_sequence<Index...>) {
        return std::make_tuple(std::end(std::get<Index>(t))...);
    }

    template <typename... Types>
    auto get_end(std::tuple<Types...>& t) {
        return get_end_impl(t, std::index_sequence_for<Types...>{});
    }

    template <typename... Types>
    auto get_end(std::tuple<Types...> const& t) {
        return get_end_impl(t, std::index_sequence_for<Types...>{});
    }

    /// @brief The actual sturcture of the zip, holding the references to thecontainers.
    /// @tparam Iterable The containers types that supports `std::begin()` and `std::end()`.
    template <typename... Iterable>
    struct Zipper {
    public:
        using Iterables = std::tuple<Iterable...>;
        using iterator = ZipperIterator<Iterables>;
        using const_iterator = ZipperIterator<Iterables>;

    public:
        Iterables iterables;

    public:
        Zipper(Iterable&&... args)
            : iterables{ std::forward<Iterable>(args)... } {}

        auto begin() { return iterator(get_begin(iterables)); }
        auto end() { return iterator(get_end(iterables)); }

        auto begin() const { return const_iterator(get_begin(iterables)); }
        auto end() const { return const_iterator(get_end(iterables)); }
    };

} // namespace ZipperDetail

/// @brief A Python-like `zip` for `C++` containers.
/// @code E.g.
/// auto zipped{ zip(std::vector{ 1, 2, 3 }, std::vector{ 4, 5, 6 }, std::vector{ 7, 8, 9 }) };
/// @endcode
template <typename... Iterable>
auto zip(Iterable&&... args) {
    return ZipperDetail::Zipper<Iterable...>{ std::forward<Iterable>(args)... };
}

template <typename... Iterable>
auto enumerate(Iterable&&... args) {
}

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_UTILS_ZIP_HPP_
