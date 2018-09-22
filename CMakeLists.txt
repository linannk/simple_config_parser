cmake_minimum_required(VERSION 3.5)
project(simple_config_parser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

add_library(simple_config_parser STATIC
    simple_config_parser.cpp)


add_executable(test_simple_config_parser test_simple_config_parser.cpp)
target_link_libraries(test_simple_config_parser simple_config_parser)

