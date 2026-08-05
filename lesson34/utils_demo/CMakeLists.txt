add_executable(test_utils test_utils.c utils.c)
target_include_directories(test_utils PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})