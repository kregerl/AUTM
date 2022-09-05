#ifndef AUTM_LOG_H
#define AUTM_LOG_H
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "autmpch.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

class Log {
public:
    static void init();

    inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }

    inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }

private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
    static std::shared_ptr<spdlog::logger> s_clientLogger;
};

#define AUTM_CORE_INFO(...) SPDLOG_LOGGER_INFO(::Log::getCoreLogger(), __VA_ARGS__)
#define AUTM_CORE_WARN(...) SPDLOG_LOGGER_WARN(::Log::getCoreLogger(), __VA_ARGS__)
#define AUTM_CORE_ERROR(...) SPDLOG_LOGGER_ERROR(::Log::getCoreLogger(), __VA_ARGS__)
#define AUTM_CORE_DEBUG(...) SPDLOG_LOGGER_DEBUG(::Log::getCoreLogger(), __VA_ARGS__)
#define AUTM_CORE_FATAL(...) SPDLOG_LOGGER_CRITICAL(::Log::getCoreLogger(), __VA_ARGS__)
#define CORE_DBGVAR(x) AUTM_CORE_DEBUG(#x " = {}", (x))

#define AUTM_INFO(...) SPDLOG_LOGGER_INFO(::Log::getClientLogger(), __VA_ARGS__)
#define AUTM_WARN(...) SPDLOG_LOGGER_WARN(::Log::getClientLogger(), __VA_ARGS__)
#define AUTM_ERROR(...) SPDLOG_LOGGER_ERROR(::Log::getClientLogger(), __VA_ARGS__)
#define AUTM_DEBUG(...) SPDLOG_LOGGER_DEBUG(::Log::getClientLogger(), __VA_ARGS__)
#define AUTM_FATAL(...) SPDLOG_LOGGER_CRITICAL(::Log::getClientLogger(), __VA_ARGS__)
#define DBGVAR(x) AUTM_DEBUG(#x " = {}", (x))

#endif
