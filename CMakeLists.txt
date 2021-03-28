cmake_minimum_required(VERSION 3.16)

project(raspberrypi-monitor VERSION 1.0.0)

set(CMAKE_C_STANDARD 99)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(BINARY_NAME raspberrypi-monitor CACHE INTERNAL "NAME of the output binary")

include_directories(${PROJECT_SOURCE_DIR}/include/)

include(${PROJECT_SOURCE_DIR}/lib/bcm2835.cmake)
include(${PROJECT_SOURCE_DIR}/lib/sds.cmake)

add_library(support STATIC
    src/support/logger.c
    src/support/signal_handler.c
)

target_link_libraries(support PRIVATE
    sds
)

add_library(hardware STATIC
    src/hardware/GPIO.c
    src/hardware/OLED.c
    src/hardware/PCA9685.c
    src/hardware/SSD1306.c
)

# https://cmake.org/cmake/help/latest/command/target_link_libraries.html#libraries-for-a-target-and-or-its-dependents
target_link_libraries(hardware PRIVATE
    bcm2835
    sds
)

add_library(gui STATIC
    src/graphics/paint.c
)

add_executable(${BINARY_NAME} src/main.c)

target_link_libraries(${BINARY_NAME} PRIVATE
    support
    hardware
    gui
)

