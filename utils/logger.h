#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

typedef enum {
    LOG_LEVEL_DEBUG = 10,
    LOG_LEVEL_INFO = 20,
    LOG_LEVEL_ERROR = 30
} LogLevel;

void log_set_level(LogLevel level);
void log_msg(LogLevel level, const char *fmt, ...);

#define LOG_DEBUG(...)   log_msg(LOG_LEVEL_DEBUG, __VA_ARGS__)
#define LOG_INFO(...)    log_msg(LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_ERROR(...)   log_msg(LOG_LEVEL_ERROR, __VA_ARGS__)

#endif