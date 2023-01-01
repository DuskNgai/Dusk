#ifndef _DUSK_LOG_HPP_
#define _DUSK_LOG_HPP_

#include <memory>

#include <spdlog/spdlog.h>

#include <Dusk/Common.hpp>

DUSK_NAMESPACE_BEGIN

/// @class: Singleton mode log system.
class Log {
private:
    static std::shared_ptr<spdlog::logger> s_core_logger;
    static std::shared_ptr<spdlog::logger> s_client_logger;

public:
    static void Initialize();

    static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_core_logger; }
    static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_client_logger; }
};

DUSK_NAMESPACE_END

// clang-format off
// Core log macros
#define DUSK_CORE_TRACE(...)    Dusk::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DUSK_CORE_DEBUG(...)    Dusk::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define DUSK_CORE_INFO(...)     Dusk::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DUSK_CORE_WARN(...)     Dusk::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DUSK_CORE_ERROR(...)    Dusk::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DUSK_CORE_CRITICAL(...) Dusk::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define DUSK_CLIENT_TRACE(...)    Dusk::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DUSK_CLIENT_DEBUG(...)    Dusk::Log::GetClientLogger()->debug(__VA_ARGS__)
#define DUSK_CLIENT_INFO(...)     Dusk::Log::GetClientLogger()->info(__VA_ARGS__)
#define DUSK_CLIENT_WARN(...)     Dusk::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DUSK_CLIENT_ERROR(...)    Dusk::Log::GetClientLogger()->error(__VA_ARGS__)
#define DUSK_CLIENT_CRITICAL(...) Dusk::Log::GetClientLogger()->critical(__VA_ARGS__)
// clang-format on

#endif // !_DUSK_LOG_HPP_
