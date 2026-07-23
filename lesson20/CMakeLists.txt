add_executable(strncpy_trap strncpy_trap.c)
add_executable(my_strstr my_strstr.c)
add_executable(safe_strcat safe_strcat.c)

# 添加测试程序，包含库文件和测试文件
add_executable(test_my_string my_string.c test_my_string.c)

# 确保头文件目录被找到（通常当前目录已经可以，但显式添加更清晰）
target_include_directories(test_my_string PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})