add_executable(led_matrix_app main.c)
target_include_directories(led_matrix_app
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(led_matrix_app PRIVATE animations_lib)