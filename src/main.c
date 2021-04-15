/**
 * File              : main.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 06.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "graphics/font.h"
#include "graphics/paint.h"
#include "hardware/OLED.h"
#include "support/logger.h"
#include "support/signal_handler.h"
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

bool DEBUG_MODE = false;

int main(int argc, char *argv[]) {
  DEBUG_MODE = true;
  log_debug("Starting %s ...\n", argv[0]);

  signal(SIGINT, quit);

  oled_turn_on();

  const char *text[] = {"!\"#$%&'()*+,-./012345", "6789:;<=>?@AaBbCcDdEe",
                        "FfGgHhIiJjKkLlMmNnOoP", "pQqRrSsTtUuVvWwXxYyZz"};
  struct font font6x8 = {6, 8};
  struct image *img = newimg_text(SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX, text,
                                  sizeof text / sizeof text[0], &font6x8);
  screen screen = cropimg(img, 0);
  oled_display(screen);

  for (;;) {
    sleep(1);
  }
  return 0;
}
