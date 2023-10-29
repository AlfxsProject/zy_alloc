cmake_minimum_required(VERSION 3.26)
project(zy_alloc C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SOURCES zy_alloc.h zy_alloc.c)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCES})