/**
 * File              : logger.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 29.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "support/logger.h"
#include <sds.h>
#include <stdarg.h>
#include <stdio.h>

static void log_msg(const char *prefix, FILE *stream, const char *msg,
                    va_list args);

extern bool DEBUG_MODE;

void log_info(const char *msg, ...) {
  va_list args;
  va_start(args, msg);

  log_msg("[ INFO] ", stdout, msg, args);

  va_end(args);
}

void log_debug(const char *msg, ...) {
  if (!DEBUG_MODE) {
    return;
  }

  va_list args;
  va_start(args, msg);

  log_msg("[DEBUG] ", stdout, msg, args);

  va_end(args);
}

void log_error(const char *msg, ...) {
  va_list args;
  va_start(args, msg);

  log_msg("[ERROR] ", stderr, msg, args);

  va_end(args);
}

static void log_msg(const char *prefix, FILE *stream, const char *msg,
                    va_list args) {
  sds msg_sds = sdsnew(prefix);
  msg_sds = sdscat(msg_sds, msg);
  vfprintf(stream, msg_sds, args);
  sdsfree(msg_sds);
}
