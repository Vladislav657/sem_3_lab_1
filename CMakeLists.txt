cmake_minimum_required(VERSION 3.29)
project(lab_1)

add_subdirectory(lib/googletest)

include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

enable_testing()
set(CMAKE_CXX_STANDARD 20)

add_executable(lab_1 main.cpp
        stack.h)
target_link_libraries(lab_1 gtest gtest_main)
target_link_libraries(lab_1 gmock gmock_main)
