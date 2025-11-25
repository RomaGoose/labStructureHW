cmake_minimum_required(VERSION 3.15)

project(input LANGUAGES C)

set(SRC input.c)

add_library(input SHARED ${SRC})
target_include_directories(input PUBLIC
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../../includes/
    ${CMAKE_SOURCE_DIR}/../../includes/
    C:/pokpok/labs/lab2/includes)