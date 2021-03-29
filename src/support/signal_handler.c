/**
 * File              : signal_handler.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 29.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "support/signal_handler.h"
#include "hardware/OLED.h"
#include "support/logger.h"
#include <signal.h>
#include <stdlib.h>

void quit(int signo) {
  switch (signo) {
  case SIGINT:
    log_info("Bye\n");
    oled_turn_off();
    exit(signo);
    break;
  case SIGTERM:
    log_error("Terminated\n");
    oled_turn_off();
    exit(signo);
    break;
  default:
    break;
  }
}
