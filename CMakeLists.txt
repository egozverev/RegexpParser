cmake_minimum_required(VERSION 3.12)
project(RegexpParser)

set(CMAKE_CXX_STANDARD 17)
SET(GCC_COVERAGE_COMPILE_FLAGS "-g --coverage -ftest-coverage -fprofile-arcs")
SET(GCC_COVERAGE_LINK_FLAGS    "--coverage -lgcov")
# declared necessary flags as constants
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
add_executable(RegexpParser main.cpp regexp_parser.h regexp_parser.cpp tests.cpp tests.h)

add_subdirectory(googletest-master)
include_directories(googletest-master/googletest/include)
include_directories(googletest-master/googlemock/include)
target_link_libraries(RegexpParser gtest gtest_main)


# changed existing flags