/**
 * File              : system_info_test.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 16.04.2021
 * Last Modified Date: 16.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "support/system_info.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

static void test_cpu_usage();

static void test_cpu_temp();

static void test_mem_usage();

static void test_ip4_address();

static void test_system_time();

bool DEBUG_MODE = true;

int main(int argc, char *argv[]) {
  printf("==== start unit test ====\n");
  test_ip4_address();
  printf("==== end unit test ====\n");
}

static void test_ip4_address() {
  char addr_buff[20];
  int i = ip4_address(addr_buff);
  assert(i == 0);
  printf("test_ip4_address: %s\n", addr_buff);
}