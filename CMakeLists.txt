cmake_minimum_required(VERSION 3.26)
project(zyalloc C)

set(CMAKE_C_STANDARD 23)

include_directories(src)

add_library(zyalloc src/zyalloc.c)