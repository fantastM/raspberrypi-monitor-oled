/**
 * File              : main.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 17.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include <arpa/inet.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "graphics/font.h"
#include "graphics/paint.h"
#include "hardware/OLED.h"
#include "support/logger.h"
#include "support/signal_handler.h"
#include "support/system_info.h"

bool DEBUG_MODE = false;

static void get_ipinfo(char *ipinfo);

static void get_cpuinfo(char *cpuinfo, unsigned long *core_time,
                        unsigned long *total_time);

static void get_meminfo(char *meminfo);

int main(int argc, char *argv[]) {
  DEBUG_MODE = true;
  log_debug("Starting %s ...\n", argv[0]);

  signal(SIGINT, quit);

  oled_turn_on();

  struct font font6x8 = {6, 8};
  struct image *img = newimg(SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX);

  // instance name
  char *nameinfo = "Name:Raspi-001";

  // IPv4 info
  char ipinfo[30];
  get_ipinfo(ipinfo);

  // CPU info
  unsigned long core_time = 0;
  unsigned long total_time = 0;
  char cpuinfo[30];
  get_cpuinfo(cpuinfo, &core_time, &total_time);

  // Memory info
  char meminfo[30];
  get_meminfo(meminfo);

  const char *text[] = {"!\"#$%&'()*+,-./012345", "6789:;<=>?@AaBbCcDdEe",
                        "FfGgHhIiJjKkLlMmNnOoP", "pQqRrSsTtUuVvWwXxYyZz"};
  text[0] = nameinfo;

  for (;;) {
    get_ipinfo(ipinfo);
    get_cpuinfo(cpuinfo, &core_time, &total_time);
    get_meminfo(meminfo);

    text[1] = ipinfo;
    text[2] = cpuinfo;
    text[3] = meminfo;

    fillimg_text(img, text, sizeof text / sizeof text[0], &font6x8);
    screen screen = cropimg(img, 0);
    oled_display(screen);
    sleep(1);
  }
}

static void get_ipinfo(char *ipinfo) {
  char addr_str[INET_ADDRSTRLEN];
  if (ip4_address(addr_str) != 0) {
    log_error("Main - get IP address info error\n");
  }

  sprintf(ipinfo, "IP:%s", addr_str);
}

static void get_cpuinfo(char *cpuinfo, unsigned long *core_time,
                        unsigned long *total_time) {
  unsigned long core_time_this = 0;
  unsigned long total_time_this = 0;
  float usage;

  if (cpu_usage(&core_time_this, &total_time_this) != 0) {
    log_error("Main - get cpu usage error\n");
  }

  if (*core_time == 0 || *total_time == 0) {
    usage = 0;
  } else {
    usage = (float)(core_time_this - *core_time) /
            (float)(total_time_this - *total_time);
  }

  sprintf(cpuinfo, "CPU Usage:%.2f%%", usage);

  *core_time = core_time_this;
  *total_time = total_time_this;
}

static void get_meminfo(char *meminfo) {
  unsigned long free_mem = 0, total_mem = 0;
  mem_usage(&free_mem, &total_mem);
  float usage = (float)(total_mem - free_mem) / (float)total_mem;
  sprintf(meminfo, "Mem Usage:%.2f%%", usage);
}