add_library(led_matrix_lib STATIC led_matrix.c)
add_library(animations_lib STATIC animations.c)

target_include_directories(led_matrix_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(animations_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(animations_lib PUBLIC led_matrix_lib)