/**
 * File              : support.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 24.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef __SUPPORT_H_
#define __SUPPORT_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UBYTE uint8_t
#define UWORD uint16_t
#define UDWORD uint32_t

extern bool DEBUG_MODE;

void log_info(const char *msg);

void log_debug(const char *msg);

void log_error(const char *msg);

void quit(int sig);

#endif
