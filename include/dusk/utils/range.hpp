#ifndef _DUSK_UTILS_RANGE_HPP_
#define _DUSK_UTILS_RANGE_HPP_

#include <type_traits>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

namespace RangerDetail {

    template <typename T>
    class RangerIterator {
    public:
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = T;
        using pointer = T const*;
        using reference = T const&;
        using iterator_category = std::random_access_iterator_tag;

    private:
        T value{};
        T const start{}, end{}, step{};

    public:
        RangerIterator() = default;
        RangerIterator(T const& value, T const& start, T const& end, T const& step)
            : value{ value }
            , start{ start }
            , end{ end }
            , step{ step } {}

    public:
        pointer operator->() const { return &this->value; }
        reference operator*() const { return this->value; }

        RangerIterator& operator++() {
            this->value += this->step;
            this->check_end();
            return *this;
        }
        RangerIterator operator++(int) {
            auto it{ *this };
            ++(*this);
            return it;
        }
        RangerIterator& operator--() {
            this->value -= this->step;
            this->check_begin();
            return *this;
        }
        RangerIterator operator--(int) {
            auto it{ *this };
            --(*this);
            return it;
        }

        RangerIterator operator+(difference_type n) const {
            auto it{ *this };
            return it += n;
        }
        RangerIterator operator-(difference_type n) const {
            auto it{ *this };
            return it -= n;
        }
        difference_type operator-(RangerIterator const& rhs) const {
            return (this->value - rhs.value) / this->step;
        }

        RangerIterator& operator+=(difference_type n) {
            this->value += this->step * n;
            this->check_end();
            return *this;
        }
        RangerIterator& operator-=(difference_type n) {
            this->value -= this->step * n;
            this->check_begin();
            return *this;
        }

        // TODO: Replace with `<=>` in C++20.
        bool operator==(RangerIterator const& rhs) const { return this->value == rhs.value; }
        bool operator!=(RangerIterator const& rhs) const { return this->value != rhs.value; }
        bool operator<(RangerIterator const& rhs) const { return this->value < rhs.value; }
        bool operator>(RangerIterator const& rhs) const { return this->value > rhs.value; }
        bool operator<=(RangerIterator const& rhs) const { return this->value <= rhs.value; }
        bool operator>=(RangerIterator const& rhs) const { return this->value >= rhs.value; }

    private:
        void check_begin() {
            this->value = (this->step > T{}) ? std::max(this->value, this->start) : std::min(this->value, this->start);
        }

        void check_end() {
            this->value = (this->step > T{}) ? std::min(this->value, this->end) : std::max(this->value, this->end);
        }
    };

    template <typename T>
    class Ranger {
    public:
        using iterator = RangerIterator<T>;
        using value_type = T;

    private:
        T const start, finish, step;

    public:
        Ranger(T const& start, T const& end, T const& step)
            : start{ start }
            , finish{ end }
            , step{ step } {}

    public:
        iterator begin() { return iterator{ this->start, this->start, this->finish, this->step }; }
        iterator end() { return iterator{ this->finish, this->start, this->finish, this->step }; }
        std::reverse_iterator<iterator> rbegin() { return std::reverse_iterator<iterator>{ this->end() }; }
        std::reverse_iterator<iterator> rend() { return std::reverse_iterator<iterator>{ this->begin() }; }
    };

} // namespace RangerDetail

/// @brief A Python-like `range`.
template <typename T>
auto range(T const& end) {
    return RangerDetail::Ranger<T>{ T{}, end, T{ 1 } };
}

template <typename T, typename U>
auto range(T const& start, U const& end) {
    using least_common_t = decltype(std::declval<decltype(std::declval<T>() + 1)>() + std::declval<decltype(std::declval<U>() - 1)>());
    return RangerDetail::Ranger<least_common_t>{ static_cast<least_common_t>(start), static_cast<least_common_t>(end), 1 };
}

template <typename T, typename U, typename V>
auto range(T const& start, U const& end, V const& step) {
    using least_common_t = decltype(std::declval<decltype(std::declval<T>() + std::declval<V>())>() + std::declval<decltype(std::declval<U>() - std::declval<V>())>());
    return RangerDetail::Ranger<least_common_t>{ static_cast<least_common_t>(start), static_cast<least_common_t>(end), static_cast<least_common_t>(step) };
}

DUSK_NAMESPACE_END

#endif // !_DUSK_UTILS_RANGE_HPP_
