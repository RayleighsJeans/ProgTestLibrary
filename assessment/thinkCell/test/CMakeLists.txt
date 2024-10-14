set(TEST_HEADERS 
    ${PROJECT_DIR}/include/keyType.hpp 
    ${PROJECT_DIR}/include/valueType.hpp 
    ${PROJECT_DIR}/include/interval_map.hpp 
)
set(TEST_INCLUDE_DIRS
    ${PROJECT_DIR}/include
    ${PROJECT_DIR}/test
)

add_executable(test_A
    testA.cpp
    ${TEST_HEADERS}
)
target_link_libraries(
    test_A
    GTest::gtest
    GTest::gtest_main)
add_test(
    NAME test_A
    COMMAND test_A
)

add_executable(test_B
    testB.cpp
    ${TEST_HEADERS}
)
target_link_libraries(
    test_B
    GTest::gtest
    GTest::gtest_main)
add_test(
    NAME test_B
    COMMAND test_B
)

add_executable(test_C
    testC.cpp
    ${TEST_HEADERS}
)
target_link_libraries(
    test_C
    GTest::gtest
    GTest::gtest_main)
add_test(
    NAME test_C
    COMMAND test_C
)