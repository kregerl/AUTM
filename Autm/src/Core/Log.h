#ifndef AUTM_LOG_H
#define AUTM_LOG_H
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "autmpch.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

class Log {
public:
    static void init();

    inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_core_logger; }

    inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_client_logger; }

private:
    static std::shared_ptr<spdlog::logger> s_core_logger;
    static std::shared_ptr<spdlog::logger> s_client_logger;
};

#define AUTM_CORE_INFO(...) SPDLOG_LOGGER_INFO(::Log::get_core_logger(), __VA_ARGS__)
#define AUTM_CORE_WARN(...) SPDLOG_LOGGER_WARN(::Log::get_core_logger(), __VA_ARGS__)
#define AUTM_CORE_ERROR(...) SPDLOG_LOGGER_ERROR(::Log::get_core_logger(), __VA_ARGS__)
#define AUTM_CORE_DEBUG(...) SPDLOG_LOGGER_DEBUG(::Log::get_core_logger(), __VA_ARGS__)
#define AUTM_CORE_FATAL(...) SPDLOG_LOGGER_CRITICAL(::Log::get_core_logger(), __VA_ARGS__)

#define AUTM_INFO(...) SPDLOG_LOGGER_INFO(::Log::get_client_logger(), __VA_ARGS__)
#define AUTM_WARN(...) SPDLOG_LOGGER_WARN(::Log::get_client_logger(), __VA_ARGS__)
#define AUTM_ERROR(...) SPDLOG_LOGGER_ERROR(::Log::get_client_logger(), __VA_ARGS__)
#define AUTM_DEBUG(...) SPDLOG_LOGGER_DEBUG(::Log::get_client_logger(), __VA_ARGS__)
#define AUTM_FATAL(...) SPDLOG_LOGGER_CRITICAL(::Log::get_client_logger(), __VA_ARGS__)
#define DBGVAR(x) AUTM_DEBUG(#x " = {}", (x))

#endif
