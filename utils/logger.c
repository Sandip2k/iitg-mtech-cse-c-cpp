#include "logger.h"
#include <stdio.h>
#include <stdlib.h>

static LogLevel g_log_level = LOG_LEVEL_INFO;

void log_set_level(LogLevel level) {
    g_log_level = level;
}

static const char *log_level_name(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_DEBUG: return "DEBUG";
        case LOG_LEVEL_INFO:  return "INFO";
        case LOG_LEVEL_ERROR: return "ERROR";
        default:              return "UNKNOWN";
    }
}

void log_msg(LogLevel level, const char *fmt, ...) {
    if (level < g_log_level) {
        return;
    }

    FILE *out = (level == LOG_LEVEL_ERROR) ? stderr : stdout;
    fprintf(out, "[%s] ", log_level_name(level));

    va_list args;
    va_start(args, fmt);
    vfprintf(out, fmt, args);
    va_end(args);

    fputc('\n', out);
    fflush(out);
}