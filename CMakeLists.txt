cmake_minimum_required(VERSION 3.15)
project(convay_gameoflife)

find_package(raylib 3.7.0 REQUIRED)

set(CMAKE_C_STANDARD 11) # Requires C11 standard

add_executable(main main.c)

target_link_libraries(main raylib m)

