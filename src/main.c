/**
 * File              : main.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 23.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "hardware/OLED.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void quit(int signo) {
  printf("quit ...\n");
  exit(0);
}

int main(int argc, char *argv[]) {
  signal(SIGINT, quit);

  char *s = "Hello, World!";
  printf("%s\n", s);
}
