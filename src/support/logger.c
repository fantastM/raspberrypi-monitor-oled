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

extern bool DEBUG_MODE;

void log_info(const char *msg, ...) {
  va_list args;
  va_start(args, msg);

  sds msg_sds = sdsnew("[ INFO] ");
  msg_sds = sdscat(msg_sds, msg);
  vprintf(msg_sds, args);
  sdsfree(msg_sds);

  va_end(args);
}

void log_debug(const char *msg, ...) {
  if (!DEBUG_MODE) {
    return;
  }

  va_list args;
  va_start(args, msg);

  sds msg_sds = sdsnew("[DEBUG] ");
  msg_sds = sdscat(msg_sds, msg);
  vprintf(msg_sds, args);
  sdsfree(msg_sds);

  va_end(args);
}

void log_error(const char *msg, ...) {
  va_list args;
  va_start(args, msg);

  sds msg_sds = sdsnew("[ERROR] ");
  msg_sds = sdscat(msg_sds, msg);
  vfprintf(stderr, msg_sds, args);
  sdsfree(msg_sds);

  va_end(args);
}
