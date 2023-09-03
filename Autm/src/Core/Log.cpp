#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::s_core_logger;
std::shared_ptr<spdlog::logger> Log::s_client_logger;

void Log::init() {
#ifdef DEBUG
    spdlog::set_pattern("%^[%T][%n] %s:%#: %v%$");
#else
    spdlog::set_pattern("%^[%T] [%n]: %v%$");
#endif
    s_core_logger = spdlog::stdout_color_mt("AUTM");
    s_core_logger->set_level(spdlog::level::trace);

    s_client_logger = spdlog::stdout_color_mt("APP");
    s_client_logger->set_level(spdlog::level::trace);
}
