cmake_minimum_required(VERSION 3.5)
project(simple_config_parser)

add_library(simple_config_parser STATIC
    simple_config_parser.cpp)


add_executable(test_simple_config_parser test_simple_config_parser.cpp)
target_link_libraries(test_simple_config_parser simple_config_parser)

