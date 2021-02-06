#ifndef LOG_HPP
#define LOG_HPP
#include <string>
#include <cassert>
#include <cstdio>

using std::string;
using std::vprintf;

enum LogLevel {
    LOG_OFF = 0,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
    LOG_TRACE,
    LOG_ALL
};

void SetLogLevel(LogLevel level);

void Logi(const char* func_name, const char* format, ...);
void Logw(const char* func_name, const char* format, ...);
void Logd(const char* func_name, const char* format, ...);
void Loge(const char* func_name, const char* format, ...);
void Logt(const char* func_name, const char* format, ...);

void Assertm(bool condition, const char* func_name, const char* format, ...);
#endif

