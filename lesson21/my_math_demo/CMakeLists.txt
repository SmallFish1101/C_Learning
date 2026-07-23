add_executable(test_math my_math.c test_math.c)
target_include_directories(test_math PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})