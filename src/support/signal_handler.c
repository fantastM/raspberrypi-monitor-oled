/**
 * File              : signal_handler.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 27.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "support/signal_handler.h"
#include "support/logger.h"
#include <signal.h>
#include <stdlib.h>

void quit(int signo) {
  if (signo == SIGTERM) {
    log_error("Bye");
    exit(signo);
  }
}
