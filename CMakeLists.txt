cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(lab2 LANGUAGES C)

set(SRC src/main.c)
add_subdirectory(src/linked_lists)
add_subdirectory(src/input)
add_executable(main ${SRC})

target_include_directories(main PUBLIC
# ${CMAKE_CURRENT_SOURCE_DIR}/../../includes/
  ${CMAKE_SOURCE_DIR}/includes
)
target_link_libraries(main 
  PUBLIC lists 
  PUBLIC input
)

