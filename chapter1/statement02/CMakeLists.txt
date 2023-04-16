get_directory_property(INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES)

if (DEFINED INCLUDE_DIRECTORIES)
    message(STATUS "Caller include directories: ${INCLUDE_DIRECTORIES}")
    include_directories(INCLUDE_DIRECTORIES)
else()
    message(FATAL_ERROR "Caller include directories not found")
endif()

include_directories(.)

add_executable(
    statement02_test
    statement02.cc
    statement02_test.cc
)
target_link_libraries(statement02_test gtest_main)
