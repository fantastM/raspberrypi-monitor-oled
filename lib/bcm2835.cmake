# https://cmake.org/cmake/help/latest/module/ExternalProject.html
include(ExternalProject)

ExternalProject_Add(bcm2835_fetch
    PREFIX              "bcm2835-1.68"
    URL                 http://www.airspayce.com/mikem/bcm2835/bcm2835-1.68.tar.gz
    URL_MD5             96ee0c2b078a77bfe4aa749fd056157a
    CONFIGURE_COMMAND   "./configure"
    BUILD_IN_SOURCE     true
    BUILD_COMMAND       "make"
    INSTALL_COMMAND     ""
)

ExternalProject_Get_Property(bcm2835_fetch SOURCE_DIR)

# https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html
add_library(bcm2835 STATIC IMPORTED)
set_target_properties(bcm2835 PROPERTIES
    # https://cmake.org/cmake/help/v3.20/manual/cmake-properties.7.html#properties-on-targets
    IMPORTED_LOCATION       ${SOURCE_DIR}/src/libbcm2835.a
    INCLUDE_DIRECTORIES     ${SOURCE_DIR}/src/
)

add_dependencies(bcm2835 bcm2835_fetch)

