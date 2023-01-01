#include <spdlog/sinks/stdout_color_sinks.h>

#include <Dusk/Log.hpp>

DUSK_NAMESPACE_BEGIN

std::shared_ptr<spdlog::logger> Log::s_core_logger;
std::shared_ptr<spdlog::logger> Log::s_client_logger;

void Log::Initialize() {
    spdlog::set_pattern("%^[%T] %n: %v%$");

    Log::s_core_logger = spdlog::stdout_color_mt("Dusk");
    Log::s_core_logger->set_level(spdlog::level::trace);

    Log::s_client_logger = spdlog::stdout_color_mt("App");
    Log::s_client_logger->set_level(spdlog::level::trace);
}

DUSK_NAMESPACE_END
