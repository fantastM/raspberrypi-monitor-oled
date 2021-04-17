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

int cpu_usage(unsigned int *core_time, unsigned int *total_time);

float cpu_temp();

float mem_usage();

int ip4_address(char *addr_buff);

char *system_time();

char *instance_name();

#endif
