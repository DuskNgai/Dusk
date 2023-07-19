#ifndef NDEBUG
    #include <dusk/log.hpp>
#endif

#include <dusk/utils/timer.hpp>

DUSK_NAMESPACE_BEGIN

std::chrono::microseconds Timer::delta_time{ std::chrono::microseconds::zero() };
Timer::clock::time_point Timer::last_time_point{ Timer::clock::now() };

void Timer::update_delta_time() {
    auto current_time_point{ Timer::clock::now() };
    Timer::delta_time = Timer::count_ticks(Timer::last_time_point, current_time_point);
    Timer::last_time_point = current_time_point;
}

float Timer::get_delta_time() {
    return std::chrono::duration_cast<std::chrono::microseconds, int64_t>(delta_time).count() / 1e6f;
}

// yyyy-mm-dd hh:mm:ss format
std::string Timer::get_current_time_string() {
    char time_buffer[24]{};
    auto current_time{ std::chrono::system_clock::now() };
    auto c_format_time{ std::chrono::system_clock::to_time_t(current_time) };
    std::strftime(time_buffer, sizeof(time_buffer), "%F %T", std::localtime(&c_format_time));
    return time_buffer;
}

bool Timer::is_running() const { return this->m_timer_status == TimerStatus::RUNNING; }

bool Timer::is_stopping() const { return this->m_timer_status == TimerStatus::STOPPING; }

//* One can figure out the relationship between these methods by a state machine.

void Timer::start() {
    // Start a new timer.
    if (this->is_stopping()) {
        this->m_elapsed_time = std::chrono::microseconds::zero();
    }
    else if (this->is_running()) {
#ifndef NDEBUG
        DUSK_CORE_WARN("Timer is running.");
#endif
        return;
    }
    // If TimerStatus::PAUSING
    this->m_start_tick = clock::now();
    this->m_timer_status = TimerStatus::RUNNING;
}

void Timer::stop() {
    if (this->is_running()) {
        this->m_end_tick = clock::now();
        this->m_elapsed_time += this->count_ticks(this->m_start_tick, this->m_end_tick);
    }
    else if (this->is_stopping()) {
#ifndef NDEBUG
        DUSK_CORE_WARN("Timer is stopping.");
#endif
        return;
    }
    // If TimerStatus::PAUSING
    this->m_timer_status = TimerStatus::STOPPING;
}

void Timer::pause() {
    if (this->is_running()) {
        this->m_end_tick = clock::now();
        this->m_elapsed_time += this->count_ticks(this->m_start_tick, this->m_end_tick);
        this->m_timer_status = TimerStatus::PAUSING;
    }
    else { // If TimerStatus::PAUSING, TimerStatus::STOPPING
#ifndef NDEBUG
        DUSK_CORE_WARN("Timer is stopping.");
#endif
    }
}

void Timer::reset() {
    this->m_elapsed_time = std::chrono::microseconds::zero();
    this->m_timer_status = TimerStatus::STOPPING;
}

std::chrono::microseconds Timer::count_ticks(clock::time_point start_tick, clock::time_point end_tick) {
    return std::chrono::duration_cast<std::chrono::microseconds>(end_tick - start_tick);
}

DUSK_NAMESPACE_END
