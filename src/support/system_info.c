/**
 * File              : system_info.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 16.04.2021
 * Last Modified Date: 16.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "support/system_info.h"
#include "support/logger.h"
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/socket.h>

static bool str_start_with(char *str, char *prefix);

int ip4_address(char *addr_str) {
  struct ifaddrs *ifaddr = NULL;
  // https://man7.org/linux/man-pages/man3/getifaddrs.3.html
  if (getifaddrs(&ifaddr) < 0) {
    log_error("Error: getifaddrs");
    return -1;
  }

  for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == NULL)
      continue;
    // filter non IPv4 family
    if (ifa->ifa_addr->sa_family != AF_INET)
      continue;

    struct sockaddr_in *sock_addr = (struct sockaddr_in *)ifa->ifa_addr;
    // https://man7.org/linux/man-pages/man3/inet_ntop.3.html
    inet_ntop(AF_INET, &(sock_addr->sin_addr), addr_str, INET_ADDRSTRLEN);

    if (str_start_with(addr_str, "127"))
      continue;
    printf("interface: %s, family: %d, ip: %s\n", ifa->ifa_name,
           ifa->ifa_addr->sa_family, addr_str);
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
