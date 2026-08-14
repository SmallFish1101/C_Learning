cmake_minimum_required(VERSION 3.10)
project(SPISim C)

add_executable(spi_sim main.c spi_sim.c)
target_include_directories(spi_sim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})