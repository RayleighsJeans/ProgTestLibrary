set(TEST_HEADERS 
    ${PROJECT_DIR}/include/operators.hpp 
    ${PROJECT_DIR}/include/evaluate.hpp
    ${PROJECT_DIR}/test/include/map.hpp
    ${PROJECT_DIR}/test/include/distributions.hpp

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

add_executable(automatic_tests
    automaticTests.cpp
    ${TEST_HEADERS}
)
target_link_libraries(
    automatic_tests
    GTest::gtest
    GTest::gtest_main)
add_test(
    NAME automatic_tests
    COMMAND automatic_tests
)