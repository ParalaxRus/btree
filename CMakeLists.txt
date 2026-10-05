cmake_minimum_required(VERSION 3.20)

project(MyCppProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(btree
    src/btree.cpp
    src/main.cpp
    src/node.cpp
)

# GoogleTest setup

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(btree_tests
    tests/node_test.cpp
    #tests/btree_test.cpp

    src/node.cpp
)

target_include_directories(btree_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(btree_tests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(btree_tests)
