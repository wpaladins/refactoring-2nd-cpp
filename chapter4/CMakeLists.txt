include_directories(.)

add_executable(
    province_test
    province_test.cc
)
target_link_libraries(province_test gtest_main)
