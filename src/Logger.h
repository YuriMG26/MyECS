#pragma once

#define LOG_GREEN "\u001b[32m"
#define LOG_RED "\u001b[31m"
#define LOG_YELLOW "\u001b[33m"
#define LOG_CYAN "\u001b[36m"
#define LOG_RESET "\u001b[0m"

#include <stdarg.h>
#include <stdio.h>

#if _WIN32
#define secure_sprintf(...) sprintf_s(__VA_ARGS__);
#else
#define secure_sprintf(...) snprintf(__VA_ARGS__);
#endif

#ifdef _MSC_VER
#define FUNCTION_SIGNATURE __FUNCSIG__
#else
#define FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#endif

namespace Logger {
void log(const char *format, ...);
void error(const char *format, ...);
void warning(const char *format, ...);
void memory(const char *format, ...);

};  // namespace Logger
