include(FetchContent)

FetchContent_Declare(
    font6x8
    GIT_REPOSITORY  https://github.com/fantasticmao/font6x8
    GIT_TAG         main
    GIT_SHALLOW     true
)

if(NOT font6x8_POPULATED)
    message(NOTICE "-- Download github.com/fantasticmao/font6x8 ing ...")
    FetchContent_Populate(font6x8)
    message(NOTICE "-- Download github.com/fantasticmao/font6x8 complete!")
    message(NOTICE "-- Build github.com/fantasticmao/font6x8 ing ...")
    message(NOTICE "-- Build github.com/fantasticmao/font6x8 complete!")
endif()

add_library(font6x8 INTERFACE)
target_include_directories(font6x8 INTERFACE
    ${font6x8_SOURCE_DIR}/
)

