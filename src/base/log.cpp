#include "base/log.hpp"

LogLevel log_level = LOG_INFO;

void SetLogLevel(LogLevel level) {
    log_level = level; 
}

#define LogDeclare(funcname, level, level_msg) \
void funcname(const char* func_name, const char* format, ...) { \
    if (log_level >= level) { \
        va_list ls; \
        va_start(ls, format); \
        printf("[%s]{%s}: ", level_msg, func_name); \
        vprintf(format, ls); \
        puts("\n"); \
        fflush(stdout); \
        va_end(ls); \
    } \
}

LogDeclare(Logi, LOG_INFO, "INFO")
LogDeclare(Logw, LOG_WARN, "WARN")
LogDeclare(Logd, LOG_DEBUG, "DEBUG")
LogDeclare(Loge, LOG_ERROR, "ERROR")
LogDeclare(Logt, LOG_TRACE, "TRACE")

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
