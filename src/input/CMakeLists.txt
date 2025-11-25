cmake_minimum_required(VERSION 3.15)

project(input LANGUAGES C)

set(SRC input.c)

add_library(input STATIC ${SRC})

target_include_directories(input PUBLIC
    ${CMAKE_SOURCE_DIR}/includes/
)

target_link_libraries(input 
  PRIVATE lists 
)
