set(TEST_HEADERS 
    ${PROJECT_DIR}/include/operators.hpp 
    ${PROJECT_DIR}/include/evaluate.hpp)
set(TEST_INCLUDE_DIRS ${PROJECT_DIR}/include ${PROJECT_DIR}/test)

add_executable(manual_tests 
    manualTests.cpp
    ${TEST_HEADERS})
target_include_directories(manual_tests PUBLIC ${TEST_INCLUDE_DIRS})
add_test(manual_tests, manual_tests)

add_executable(automatic_tests 
    automaticTests.cpp
    ${TEST_HEADERS})
target_include_directories(automatic_tests PUBLIC ${TEST_INCLUDE_DIRS})
add_test(automatic_tests, automatic_tests)