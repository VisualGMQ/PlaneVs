#include "base/log.hpp"

LogLevel log_level = LOG_INFO;

void SetLogLevel(LogLevel level) {
    log_level = level; 
}

#define LOG_PRINT(level, level_msg, func_name, start_arg) \
    if (level <= log_level) { \
        va_list ls; \
        va_start(ls, format); \
        printf("[%s]{%s}: ", level_msg, func_name); \
        vprintf(format, ls); \
        puts("\n"); \
        fflush(stdout); \
        va_end(ls); \
    } \

void Logi(const char* func_name, const char* format, ...) {
    LOG_PRINT(LOG_INFO, "INFO", func_name, format);
}

void Logw(const char* func_name, const char* format, ...) {
    LOG_PRINT(LOG_WARN, "WARN", func_name, format);
}

void Logd(const char* func_name, const char* format, ...) {
    LOG_PRINT(LOG_DEBUG, "DEBUG", func_name, format);
}

void Loge(const char* func_name, const char* format, ...) {
    LOG_PRINT(LOG_ERROR, "ERROR", func_name, format);
}

void Logt(const char* func_name, const char* format, ...) {
    LOG_PRINT(LOG_TRACE, "TRACE", func_name, format);
}

#undef LogDeclare

void Assertm(bool condition, const char* func_name, const char* format, ...) {
    if (!condition) {
        va_list ls;
        va_start(ls, format);
        printf("[%s]: ", func_name);
        vprintf(format, ls);
        puts("\n");
        fflush(stdout);
        va_end(ls);
        assert(false);
    }
}
