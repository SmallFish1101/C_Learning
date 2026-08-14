add_library(snake_lib STATIC snake.c)
target_include_directories(snake_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)