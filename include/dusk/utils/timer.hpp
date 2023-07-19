#ifndef _DUSK_UTILS_TIMER_HPP_
#define _DUSK_UTILS_TIMER_HPP_

#include <chrono>
#include <string>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

/// @class The timer and clock class.
class Timer {
public:
    // clang-format off
    enum class TimerStatus : int32_t { STOPPING, RUNNING, PAUSING };
    using clock = std::chrono::steady_clock;
    // clang-format on

private:
    static std::chrono::microseconds delta_time;
    static clock::time_point last_time_point;

    clock::time_point m_start_tick;
    clock::time_point m_end_tick;
    TimerStatus m_timer_status{ TimerStatus::STOPPING };
    std::chrono::microseconds m_elapsed_time{ 0 };

public:
    Timer() = default;
    Timer(Timer const &) = delete;
    Timer &operator=(Timer const &) = delete;
    ~Timer() = default;

public:
    /// @brief Update the delta time between frames
    static void update_delta_time();

    /// @brief Get the floating point value of the delta time.
    /// Default unit: `seconds`.
    static float get_delta_time();

    /// @brief Get the current time string in yyyy-mm-dd hh:mm:ss format.
    static std::string get_current_time_string();

    bool is_running() const;
    bool is_stopping() const;

    void start();
    void stop();
    void pause();

    /// @brief Resets the accumulated time to 0.
    /// You don't need to reset a timer if the timer is stopping.
    void reset();

    /// @brief A template member function for representing time in various formats.
    /// Default unit: `milliseconds`.
    template <typename duration_t = std::chrono::milliseconds>
    int64_t get_elapsed_time() const {
        return std::chrono::duration_cast<duration_t, int64_t>(this->m_elapsed_time).count();
    }

private:
    static std::chrono::microseconds count_ticks(clock::time_point start_tick, clock::time_point end_tick);
};

DUSK_NAMESPACE_END

#endif // !_DUSK_UTILS_TIMER_HPP_
