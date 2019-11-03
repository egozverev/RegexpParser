cmake_minimum_required(VERSION 3.12)
project(RegexpParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(RegexpParser main.cpp regexp_parser.h regexp_parser.cpp)

add_subdirectory(googletest-master)
include_directories(googletest-master/googletest/include)
include_directories(googletest-master/googlemock/include)
target_link_libraries(RegexpParser gtest gtest_main)