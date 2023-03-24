#ifndef _DUSK_LOG_HPP_
#define _DUSK_LOG_HPP_

#include <memory>

#include <spdlog/spdlog.h>

#include <dusk/common.hpp>

DUSK_NAMESPACE_BEGIN

/// @class: Singleton mode log system.
class Log {
private:
    static std::shared_ptr<spdlog::logger> s_core_logger;
    static std::shared_ptr<spdlog::logger> s_client_logger;

public:
    static void init();

    static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_core_logger; }
    static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_client_logger; }
};

DUSK_NAMESPACE_END

// clang-format off
// Core log macros
#define DUSK_CORE_TRACE(...)    dusk::Log::get_core_logger()->trace(__VA_ARGS__)
#define DUSK_CORE_DEBUG(...)    dusk::Log::get_core_logger()->debug(__VA_ARGS__)
#define DUSK_CORE_INFO(...)     dusk::Log::get_core_logger()->info(__VA_ARGS__)
#define DUSK_CORE_WARN(...)     dusk::Log::get_core_logger()->warn(__VA_ARGS__)
#define DUSK_CORE_ERROR(...)    dusk::Log::get_core_logger()->error(__VA_ARGS__)
#define DUSK_CORE_CRITICAL(...) dusk::Log::get_core_logger()->critical(__VA_ARGS__)

// Client log macros
#define DUSK_CLIENT_TRACE(...)    dusk::Log::get_client_logger()->trace(__VA_ARGS__)
#define DUSK_CLIENT_DEBUG(...)    dusk::Log::get_client_logger()->debug(__VA_ARGS__)
#define DUSK_CLIENT_INFO(...)     dusk::Log::get_client_logger()->info(__VA_ARGS__)
#define DUSK_CLIENT_WARN(...)     dusk::Log::get_client_logger()->warn(__VA_ARGS__)
#define DUSK_CLIENT_ERROR(...)    dusk::Log::get_client_logger()->error(__VA_ARGS__)
#define DUSK_CLIENT_CRITICAL(...) dusk::Log::get_client_logger()->critical(__VA_ARGS__)
// clang-format on

#endif // !_DUSK_LOG_HPP_
