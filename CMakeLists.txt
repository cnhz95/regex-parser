cmake_minimum_required(VERSION 3.24)
project(regex_parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(regex_parser main.cpp lexer.h parser.h nodes.h parser.cpp lexer.cpp)
