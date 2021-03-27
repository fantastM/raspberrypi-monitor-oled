/**
 * File              : main.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 27.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "support/logger.h"
#include "support/signal_handler.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool DEBUG_MODE = false;

int main(int argc, char *argv[]) {
  DEBUG_MODE = false;
  log_debug("Starting ...");

  signal(SIGINT, quit);

  for (;;) {
    sleep(1);
  }
  return 0;
}
