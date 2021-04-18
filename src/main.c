/**
 * File              : main.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 18.04.2021
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

static void get_ip_info(char *ip_info);

static void get_cpu_usage_info(char *cpu_usage_info, unsigned long *core_time,
                               unsigned long *total_time);

static void get_cpu_temp_info(char *cpu_temp_info);

static void get_mem_usage_info(char *mem_usage_info);

int main(int argc, char *argv[]) {
  DEBUG_MODE = true;
  log_debug("Starting %s ...\n", argv[0]);

  signal(SIGINT, quit);

  oled_turn_on();

  struct font font6x8 = {6, 8};
  struct image *img = newimg(SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX);

  // instance name
  char *name_info = "Name:Raspi-001";

  // IPv4 info
  char ip_info[30];

  // CPU usage info
  unsigned long core_time = 0;
  unsigned long total_time = 0;
  char cpu_usage_info[30];

  // CPU temp info
  char cpu_temp_info[30];

  // Memory usage info
  char mem_usage_info[30];

  // 0: instance name, 1: ip address, 2: cpu usage
  // 3: cpu temperature, 4: mem usage
  const uint8_t pages = 5;
  const char *text[pages];
  const uint8_t pages_overflow = pages - SCREEN_PAGE_NUM;

  text[0] = name_info;
  for (int i = 0, down = true;;) {
    get_ip_info(ip_info);
    get_cpu_usage_info(cpu_usage_info, &core_time, &total_time);
    get_cpu_temp_info(cpu_temp_info);
    get_mem_usage_info(mem_usage_info);

    text[1] = ip_info;
    text[2] = cpu_usage_info;
    text[3] = cpu_temp_info;
    text[4] = mem_usage_info;

    fillimg_text(img, text, sizeof text / sizeof text[0], &font6x8);
    screen screen = cropimg(img, i);
    oled_display(screen);
    i = i + (down ? 1 : -1);
    if (i >= pages_overflow || i <= 0) {
      down = !down;
    }
    sleep(1);
  }
}

static void get_ip_info(char *ip_info) {
  char addr_str[INET_ADDRSTRLEN];
  if (ip4_address(addr_str) != 0) {
    log_error("Main -- get IP address info error\n");
  }

  sprintf(ip_info, "IP:%s", addr_str);
}

static void get_cpu_usage_info(char *cpu_usage_info, unsigned long *core_time,
                               unsigned long *total_time) {
  unsigned long core_time_this = 0;
  unsigned long total_time_this = 0;
  float usage;

  if (cpu_usage(&core_time_this, &total_time_this) != 0) {
    log_error("Main -- get CPU usage error\n");
  }

  if (*core_time == 0 || *total_time == 0) {
    usage = 0;
  } else {
    usage = (float)(core_time_this - *core_time) /
            (float)(total_time_this - *total_time);
  }

  sprintf(cpu_usage_info, "CPU Usage:%.2f%%", usage * 100);

  *core_time = core_time_this;
  *total_time = total_time_this;
}

static void get_cpu_temp_info(char *cpu_temp_info) {
  unsigned int temp = 0;
  if (cpu_temp(&temp) != 0) {
    log_error("Main -- get CPU temperature error\n");
  }

  sprintf(cpu_temp_info, "CPU Temp:%dC", temp / 1000);
}

static void get_mem_usage_info(char *mem_usage_info) {
  unsigned long free_mem = 0, total_mem = 0;
  if (mem_usage(&free_mem, &total_mem) != 0) {
    log_error("Main -- get memory usage error\n");
  }
  float usage = (float)(total_mem - free_mem) / (float)total_mem;
  sprintf(mem_usage_info, "Mem Usage:%.2f%%", usage * 100);
}