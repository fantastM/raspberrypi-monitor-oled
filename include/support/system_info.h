/**
 * File              : system_info.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 06.04.2021
 * Last Modified Date: 16.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef __SYSTEM_INFO_H_
#define __SYSTEM_INFO_H_

int ip4_address(char *addr_buff);

int cpu_usage(unsigned long *core_time, unsigned long *total_time);

float cpu_temp();

int mem_usage(unsigned long *free_mem, unsigned long *total_mem);

#endif
