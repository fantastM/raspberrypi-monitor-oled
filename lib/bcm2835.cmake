# https://cmake.org/cmake/help/latest/module/FetchContent.html
include(FetchContent)

FetchContent_Declare(
    bcm2835
    URL         http://www.airspayce.com/mikem/bcm2835/bcm2835-1.68.tar.gz
    URL_MD5     96ee0c2b078a77bfe4aa749fd056157a
)

if(NOT bcm2835_POPULATED)
    message(NOTICE "-- Download bcm2835 ing ...")
    FetchContent_Populate(bcm2835)
    message(NOTICE "-- Download bcm2835 complete!")
    message(NOTICE "-- Build bcm2835 ing ...")
    # https://cmake.org/cmake/help/latest/command/execute_process.html
    execute_process(
        COMMAND             "./configure"
        COMMAND             "make"
        WORKING_DIRECTORY   ${bcm2835_SOURCE_DIR}
        RESULT_VARIABLE     bcm2835_RESULT
    )
    message(NOTICE "-- Build bcm2835 complete! execute result: ${bcm2835_RESULT}.")
endif()

# https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html
add_library(bcm2835 STATIC IMPORTED)
set_target_properties(bcm2835 PROPERTIES
    # https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#properties-on-targets
    IMPORTED_LOCATION               ${bcm2835_SOURCE_DIR}/src/libbcm2835.a
    INTERFACE_INCLUDE_DIRECTORIES   ${bcm2835_SOURCE_DIR}/src/
)

