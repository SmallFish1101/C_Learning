cmake_minimum_required(VERSION 3.10)
project(multi_apps C)

add_executable(my_greeting hello.c)
add_executable(practice practice.c)
add_executable(goodbye goodbye.c)
add_subdirectory(lesson6)