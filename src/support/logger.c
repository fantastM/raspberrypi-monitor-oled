/**
 * File              : logger.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 24.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "support.h"

void log_info(const char *msg) { printf("[ INFO] %s\n", msg); }

void log_debug(const char *msg) {
  if (DEBUG_MODE) {
    printf("[DEBUG] %s\n", msg);
  }
}

void log_error(const char *msg) { fprintf(stderr, "[ERROR] %s\n", msg); }
