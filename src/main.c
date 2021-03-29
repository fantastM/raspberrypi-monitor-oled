/**
 * File              : main.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 29.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
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

  struct image *img = newimg(SCREEN_WIDTH, SCREEN_HEIGHT);
  for (int i = 0; i < SCREEN_WIDTH * PAGE_LEN; i++) {
    *img->buf = 0x18;
  }
  screen screen = img_crop(img, 0);
  oled_display(screen);

  for (;;) {
    sleep(1);
  }
  return 0;
}
