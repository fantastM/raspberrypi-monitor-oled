/**
 * File              : font.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 31.03.2021
 * Last Modified Date: 02.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "graphics/font.h"
#include "support/logger.h"
#include <font6x8.h>
#include <signal.h>

fontbuf char_to_fontbuf(const char c) {
  if (c < 0 || c > 0x7F) {
    log_error("Font unsupport char: '%c'\n", c);
    raise(SIGTERM);
  }
  return (fontbuf)font6x8_ascii[c];
}
