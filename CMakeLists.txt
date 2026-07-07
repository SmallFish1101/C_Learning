cmake_minimum_required(VERSION 3.10)
project(multi_apps C)
set(CMAKE_C_STANDARD 11)

add_executable(my_greeting hello.c)
add_executable(practice practice.c)
add_executable(goodbye goodbye.c)
add_subdirectory(lesson6)
add_subdirectory(lesson7)