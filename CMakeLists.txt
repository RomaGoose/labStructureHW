cmake_minimum_required(VERSION 3.15)

project(lab2 LANGUAGES C)

set(SRC src/main.c)
add_subdirectory(src/linked_lists)
add_subdirectory(src/input)
add_executable(main ${SRC})

target_include_directories(main PUBLIC
# ${CMAKE_CURRENT_SOURCE_DIR}/../../includes/
${CMAKE_SOURCE_DIR}/includes
C:/pokpok/labs/lab2/includes)
target_link_libraries(main src/lists src/input)