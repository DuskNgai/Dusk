#ifndef _DUSK_CORE_UTILS_RANGE_HPP_
#define _DUSK_CORE_UTILS_RANGE_HPP_

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

namespace RangerDetail {

    template <typename T>
    struct RangerIterator {
    public:
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = T;
        using pointer = T const*;
        using reference = T const&;
        using iterator_category = std::random_access_iterator_tag;

    public:
        T value{};
        T const &start{}, end{}, step{};

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
    struct Ranger {
    public:
        using iterator = RangerIterator<T>;
        using value_type = T;

    public:
        T m_start, m_end, m_step;

    public:
        Ranger(T const& start, T const& end, T const& step)
            : m_start{ start }
            , m_end{ end }
            , m_step{ step } {}

    public:
        iterator begin() { return iterator{ this->m_start, this->m_start, this->m_end, this->m_step }; }
        iterator end() { return iterator{ this->m_end, this->m_start, this->m_end, this->m_step }; }
    };

} // namespace RangerDetail

/// @brief A Python-like `range`.
template <typename T>
auto range(T const& end) {
    return RangerDetail::Ranger<T>{ T{}, end, T{ 1 } };
}

template <typename T>
auto range(T const& start, T const& end) {
    return RangerDetail::Ranger<T>{ start, end, T{ 1 } };
}

template <typename T>
auto range(T const& start, T const& end, T const& step) {
    return RangerDetail::Ranger<T>{ start, end, step };
}

DUSK_NAMESPACE_END

#endif // !_DUSK_CORE_UTILS_RANGE_HPP_
