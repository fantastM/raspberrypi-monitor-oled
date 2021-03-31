include(FetchContent)

FetchContent_Declare(
    font8_8
    GIT_REPOSITORY      https://github.com/dhepper/font8x8/
    SOURCE_SUBDIR       master
    GIT_SHALLOW         true
)

if(NOT font8_8_POPULATED)
    message(NOTICE "-- Download github.com/dhepper/font8x8/ ing ...")
    FetchContent_Populate(font8_8)
    message(NOTICE "-- Download github.com/dhepper/font8x8/ complete!")
    message(NOTICE "-- Build github.com/dhepper/font8x8/ ing ...")
    message(NOTICE "-- Build github.com/dhepper/font8x8/ complete!")
endif()

add_library(font8_8 STATIC IMPORTED)
set_target_properties(font8_8 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES   ${font8_8_SOURCE_DIR}/
)

