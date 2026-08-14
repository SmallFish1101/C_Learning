add_executable(snake_app main.c)
target_include_directories(snake_app
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(snake_app PRIVATE snake_lib)