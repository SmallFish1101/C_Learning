# 测试程序依赖 logger.c（辅助函数）和 test_logger.c
add_executable(test_logger test_logger.c logger.c)

# 包含当前目录，以便 test_logger.c 能找到 logger.h
target_include_directories(test_logger PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 【关键】通过 CMake 定义 LOG_LEVEL 宏的值为 3（全部输出）
# 你可以修改这个值，或者创建多个 target 来体验不同级别。
target_compile_definitions(test_logger PRIVATE LOG_LEVEL=3)

# 可选：再创建一个仅输出错误的版本，用于对比
add_executable(test_logger_quiet test_logger.c logger.c)
target_include_directories(test_logger_quiet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(test_logger_quiet PRIVATE LOG_LEVEL=1)