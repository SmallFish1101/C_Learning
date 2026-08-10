add_executable(grade_app main.c)

target_include_directories(grade_app
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(grade_app PRIVATE student_lib utils_lib)