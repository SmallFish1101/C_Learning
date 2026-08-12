add_executable(ring_buffer_app main.c)

target_include_directories(ring_buffer_app
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(ring_buffer_app PRIVATE ring_buffer_lib)