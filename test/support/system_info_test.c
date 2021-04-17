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

static void test_ip4_address();

static void test_cpu_usage();

static void test_cpu_temp();

static void test_mem_usage();

bool DEBUG_MODE = true;

int main(int argc, char *argv[]) {
  printf("==== start unit test ====\n");
  test_ip4_address();
  test_cpu_usage();
  test_mem_usage();
  printf("==== end unit test ====\n");
}

static void test_ip4_address() {
  char addr_buff[20];
  int i = ip4_address(addr_buff);
  assert(i == 0);
  printf("[test_ip4_address] ip: %s\n", addr_buff);
}

static void test_cpu_usage() {
  unsigned long core_time;
  unsigned long total_time;
  int i = cpu_usage(&core_time, &total_time);
  assert(i == 0);
  printf("[test_cpu_usage] core time: %lu, total time: %lu\n", core_time,
         total_time);
}

static void test_mem_usage() {
  unsigned long free_mem;
  unsigned long total_mem;
  int i = mem_usage(&free_mem, &total_mem);
  assert(i == 0);
  printf("[test_mem_usage] memory total: %lu, memory free: %lu\n", total_mem,
         free_mem);
}