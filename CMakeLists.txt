cmake_minimum_required(VERSION 3.16)

project(raspberrypi-monitor-oled)

set(CMAKE_C_STANDARD 99)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(BINARY_NAME raspberrypi-monitor CACHE INTERNAL "NAME of output binaries")

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_library(gui_library
    src/gui/image.c
)

add_library(hardware_library
   src/hardware/GPIO.c
   src/hardware/OLED.c
   src/hardware/PCA9685.c
   src/hardware/SSD1306.c
)

add_library(support_library
    src/support/logger.c
    src/support/signal_handler.c
)

add_executable(${BINARY_NAME} src/main.c)

target_link_libraries(${BINARY_NAME}
    gui_library
    hardware_library
    support_library
)
