#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::s_coreLogger;
std::shared_ptr<spdlog::logger> Log::s_clientLogger;

void Log::init() {

#ifdef DEBUG
    spdlog::set_pattern("%^[%T][%n] %s:%#: %v%$");
#else
    spdlog::set_pattern("%^[%T] [%n]: %v%$");
#endif
    s_coreLogger = spdlog::stdout_color_mt("AUTM");
    s_coreLogger->set_level(spdlog::level::trace);

    s_clientLogger= spdlog::stdout_color_mt("APP");
    s_clientLogger->set_level(spdlog::level::trace);
}
