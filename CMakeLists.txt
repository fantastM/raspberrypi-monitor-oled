cmake_minimum_required(VERSION 3.16)

project(raspberrypi-monitor-oled)

set(CMAKE_C_STANDARD 99)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

add_executable(raspberrypi-monitor src/main.c)
