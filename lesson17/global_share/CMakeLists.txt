# 将 main.c 和 config.c 编译链接成一个可执行文件
add_executable(global_share main.c config.c)
# 将当前目录添加到头文件搜索路径，确保 main.c 能找到 config.h
target_include_directories(global_share PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})