cmake_minimum_required(VERSION 3.29)
project(lab_1)

add_subdirectory(lib/googletest)
add_subdirectory(lib/benchmark)

include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
include_directories(lib/benchmark/include)

enable_testing()
set(CMAKE_CXX_STANDARD 20)

add_executable(lab_1 main.cpp
        stack.h
)

target_link_libraries(lab_1 gtest gtest_main)
target_link_libraries(lab_1 gmock gmock_main)
target_link_libraries(lab_1 benchmark::benchmark)
