cmake_minimum_required(VERSION 3.15)

project(lists LANGUAGES C)

set(SRC list_class.c)

add_library(lists SHARED ${SRC})
target_include_directories(lists PUBLIC
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../../includes/
    ${CMAKE_SOURCE_DIR}/../../includes/
    C:/pokpok/labs/lab2/includes)