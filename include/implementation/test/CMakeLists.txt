set(TEST_HEADERS 
    ${PROJECT_DIR}/graphs/adjacencyImpl.hpp
    ${PROJECT_DIR}/graphs/basicGraphImpl.hpp
    ${PROJECT_DIR}/graphs/graphImpl.hpp
    ${PROJECT_DIR}/graphs/vertexImpl.hpp
    ${PROJECT_DIR}/lists/linkedListImpl.hpp
    ${PROJECT_DIR}/lists/nodesImpl.hpp
    ${PROJECT_DIR}/tables/hashTableImpl.hpp
    ${PROJECT_DIR}/trees/basicTreeImpl.hpp
    ${PROJECT_DIR}/trees/treeAVLImpl.hpp
)
set(TEST_INCLUDE_DIRS
    ${PROJECT_DIR}/graphs
    ${PROJECT_DIR}/lists
    ${PROJECT_DIR}/tables
    ${PROJECT_DIR}/trees
    ${PROJECT_DIR}/test
)

add_executable(nodesTest
    nodesTest.cpp
    ${TEST_HEADERS}
)
target_link_libraries(
    nodesTest
    GTest::gtest
    GTest::gtest_main)
add_test(
    NAME nodesTest
    COMMAND nodesTest
)

add_executable(linkedListTest
    linkedListTest.cpp
    ${TEST_HEADERS}
)
target_link_libraries(
    linkedListTest
    GTest::gtest
    GTest::gtest_main)
add_test(
    NAME linkedListTest
    COMMAND linkedListTest
)

add_executable(doubleLinkedListTest
    doubleLinkedListTest.cpp
    ${TEST_HEADERS}
)
target_link_libraries(
    doubleLinkedListTest
    GTest::gtest
    GTest::gtest_main)
add_test(
    NAME doubleLinkedListTest
    COMMAND doubleLinkedListTest
)

# add_executable(hashTableTest
#     hashTableTest.cpp
#     ${TEST_HEADERS}
# )
# target_link_libraries(
#     hashTableTest
#     GTest::gtest
#     GTest::gtest_main)
# add_test(
#     NAME hashTableTest
#     COMMAND hashTableTest
# )

# add_executable(adjacencyTest
#     adjacencyTest.cpp
#     ${TEST_HEADERS}
# )
# target_link_libraries(
#     adjacencyTest
#     GTest::gtest
#     GTest::gtest_main)
# add_test(
#     NAME adjacencyTest
#     COMMAND adjacencyTest
# )