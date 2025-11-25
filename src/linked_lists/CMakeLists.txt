cmake_minimum_required(VERSION 3.15)

project(lists LANGUAGES C)

set(SRC list_class.c)

add_library(lists STATIC ${SRC})
target_include_directories(lists PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../includes/
)
