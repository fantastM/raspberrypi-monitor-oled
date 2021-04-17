/**
 * File              : system_info.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 16.04.2021
 * Last Modified Date: 16.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "support/system_info.h"

#include <arpa/inet.h>
#include <errno.h>
#include <ifaddrs.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "support/logger.h"

static bool str_start_with(char *str, char *prefix);

int cpu_usage(unsigned int *core_time, unsigned int *total_time) {
  char *path = "/proc/stat";
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    log_error("SystemInfo: %s \"%s\"\n", strerror(errno), path);
    return 0;
  }

  char buff[100];
  if (fgets(buff, 100, file) == NULL) {
    log_error("SystemInfo: read file error\"%s\"\n", path);
    return 0;
  }

  unsigned int user = 0, nice = 0, system = 0;
  unsigned int idle = 0, iowait = 0, irq = 0, softirq = 0, steal = 0, guest = 0,
               guest_nice = 0;
  int i =
      sscanf(buff, "cpu %u %u %u %u %u %u %u %u %u %u", &user, &nice, &system,
             &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
  if (i != EOF && i < 10) {
    log_error("SystemInfo: scan file error\"%s\"\n", path);
  }

  *core_time = user + nice + system;
  *total_time = user + nice + system + idle + iowait + irq + softirq + steal +
                guest + guest_nice;

  fclose(file);
  return 0;
}

int ip4_address(char *addr_str) {
  struct ifaddrs *ifaddr = NULL;
  // https://man7.org/linux/man-pages/man3/getifaddrs.3.html
  if (getifaddrs(&ifaddr) < 0) {
    log_error("SystemInfo: getifaddrs\n");
    return -1;
  }

  for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == NULL) continue;
    // filter non IPv4 family
    if (ifa->ifa_addr->sa_family != AF_INET) continue;

    struct sockaddr_in *sock_addr = (struct sockaddr_in *)ifa->ifa_addr;
    // https://man7.org/linux/man-pages/man3/inet_ntop.3.html
    inet_ntop(AF_INET, &(sock_addr->sin_addr), addr_str, INET_ADDRSTRLEN);

    if (!str_start_with(addr_str, "127")) {
      break;
    }
  }

  freeifaddrs(ifaddr);
  return 0;
}

static bool str_start_with(char *str, char *prefix) {
  for (; *str != '\0' && *prefix != '\0';) {
    if (*str++ != *prefix++) {
      return false;
    }
  }
  return true;
}
