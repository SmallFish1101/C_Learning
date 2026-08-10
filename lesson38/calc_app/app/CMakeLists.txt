add_executable(calc_app main.c)
target_include_directories(calc_app
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(calc_app PRIVATE calc_parser)