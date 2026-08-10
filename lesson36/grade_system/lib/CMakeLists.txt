add_library(student_lib STATIC student.c)
add_library(utils_lib  STATIC utils.c)

target_include_directories(student_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
target_include_directories(utils_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)