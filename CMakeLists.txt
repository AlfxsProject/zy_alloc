cmake_minimum_required(VERSION 3.26)
project(zyalloc C)

set(CMAKE_C_STANDARD 23)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.c)

set(SOURCES ${SOURCES})

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCES})