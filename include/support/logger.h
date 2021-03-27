/**
 * File              : logger.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 25.03.2021
 * Last Modified Date: 25.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef __LOGGER_H_
#define __LOGGER_H_

#include <stdbool.h>

extern bool DEBUG_MODE;

void log_info(const char *msg);

void log_debug(const char *msg);

void log_error(const char *msg);

#endif
