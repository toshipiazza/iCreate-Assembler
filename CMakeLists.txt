cmake_minimum_required(VERSION 3.0)

add_subdirectory(ast)
add_subdirectory(parser)

add_executable(iCreate iCreate.c getopt.c)
target_link_libraries(iCreate ast parser)