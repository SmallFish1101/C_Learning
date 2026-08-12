add_library(calc_stack STATIC calc_stack.c)
add_library(calc_parser STATIC calc_parser.c)

target_include_directories(calc_stack
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(calc_parser
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(calc_parser PUBLIC calc_stack)
target_link_libraries(calc_parser PUBLIC calc_stack m)