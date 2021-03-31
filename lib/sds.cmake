include(FetchContent)

FetchContent_Declare(
    sds
    GIT_REPOSITORY      https://github.com/antirez/sds
    SOURCE_SUBDIR       master
    GIT_SHALLOW         true
)

if(NOT sds_POPULATED)
    message(NOTICE "-- Download github.com/antirez/sds ing ...")
    FetchContent_Populate(sds)
    message(NOTICE "-- Download github.com/antirez/sds complete!")
    message(NOTICE "-- Build github.com/antirez/sds ing ...")
    execute_process(
        COMMAND bash "-c" "cc -c sds.c sds.h sdsalloc.h && ar rc libsds.a sds.o"
        WORKING_DIRECTORY   ${sds_SOURCE_DIR}
        RESULT_VARIABLE     sds_RESULT
    )
    message(NOTICE "-- Build github.com/antirez/sds complete! Result code: ${sds_RESULT}")
endif()

add_library(sds STATIC IMPORTED)
set_target_properties(sds PROPERTIES
    IMPORTED_LOCATION               ${sds_SOURCE_DIR}/libsds.a
    INTERFACE_INCLUDE_DIRECTORIES   ${sds_SOURCE_DIR}/
)
