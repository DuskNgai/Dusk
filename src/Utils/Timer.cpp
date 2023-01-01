#ifndef NDEBUG
    #include <Dusk/Log.hpp>
#endif

#include <Dusk/Utils/Timer.hpp>

DUSK_NAMESPACE_BEGIN

std::chrono::microseconds Timer::delta_time = std::chrono::microseconds::zero();
Timer::clock::time_point Timer::last_time_point = Timer::clock::now();

void Timer::UpdateDeltaTime() {
    auto current_time_point = clock::now();
    Timer::delta_time = Timer::CountTicks(Timer::last_time_point, current_time_point);
    Timer::last_time_point = current_time_point;
}

float Timer::GetDeltaTime() {
    return std::chrono::duration_cast<std::chrono::microseconds, int64_t>(delta_time).count() / 1e6;
}

// yyyy-mm-dd hh:mm:ss format
std::string Timer::GetCurrentTimeString() {
    char time_buffer[24]{};
    auto current_time = std::chrono::system_clock::now();
    auto c_format_time = std::chrono::system_clock::to_time_t(current_time);
    std::strftime(time_buffer, sizeof(time_buffer), "%F %T", std::localtime(&c_format_time));
    return time_buffer;
}

bool Timer::IsRunning() const { return this->m_timer_status == TimerStatus::RUNNING; }

bool Timer::IsStopping() const { return this->m_timer_status == TimerStatus::STOPPING; }

//* One can figure out the relationship between these methods by a state machine.

void Timer::Start() {
    // Start a new timer.
    if (this->IsStopping()) {
        this->m_elapsed_time = std::chrono::microseconds::zero();
    }
    else if (this->IsRunning()) {
#ifndef NDEBUG
        DUSK_CORE_WARN("Timer is running.");
#endif
        return;
    }
    // If TimerStatus::PAUSING
    this->m_start_tick = clock::now();
    this->m_timer_status = TimerStatus::RUNNING;
}

void Timer::Stop() {
    if (this->IsRunning()) {
        this->m_end_tick = clock::now();
        this->m_elapsed_time += this->CountTicks(this->m_start_tick, this->m_end_tick);
    }
    else if (this->IsStopping()) {
#ifndef NDEBUG
        DUSK_CORE_WARN("Timer is stopping.");
#endif
        return;
    }
    // If TimerStatus::PAUSING
    this->m_timer_status = TimerStatus::STOPPING;
}

void Timer::Pause() {
    if (this->IsRunning()) {
        this->m_end_tick = clock::now();
        this->m_elapsed_time += this->CountTicks(this->m_start_tick, this->m_end_tick);
        this->m_timer_status = TimerStatus::PAUSING;
    }
    else { // If TimerStatus::PAUSING, TimerStatus::STOPPING
#ifndef NDEBUG
        DUSK_CORE_WARN("Timer is stopping.");
#endif
    }
}

void Timer::Reset() {
    this->m_elapsed_time = std::chrono::microseconds::zero();
    this->m_timer_status = TimerStatus::STOPPING;
}

std::chrono::microseconds Timer::CountTicks(clock::time_point start_tick, clock::time_point end_tick) {
    return std::chrono::duration_cast<std::chrono::microseconds>(end_tick - start_tick);
}

DUSK_NAMESPACE_END
