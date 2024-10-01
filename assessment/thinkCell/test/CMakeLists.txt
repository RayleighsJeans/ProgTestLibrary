set(TEST_HEADERS 
    ${PROJECT_DIR}/include/interval_map.hpp 
)
set(TEST_INCLUDE_DIRS
    ${PROJECT_DIR}/include
    ${PROJECT_DIR}/test
)

add_executable(manual_tests
    manualTests.cpp
    ${TEST_HEADERS}
)
target_link_libraries(
    manual_tests
    GTest::gtest
    GTest::gtest_main)
add_test(
    NAME manual_tests
    COMMAND manual_tests
)