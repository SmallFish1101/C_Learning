/*
 * test_logger.c
 * 测试日志模块：调用不同级别的日志宏，观察编译结果。
 *
 * 运行前无需修改源码，只需通过 CMake 或 -D 选项改变 LOG_LEVEL 的值，
 * 即可控制输出哪些日志。
 */

#include "logger.h"
#include <stdio.h>   // printf

int main(void)
{
    printf("=== Logger Demo ===\n");
    printf("Current LOG_LEVEL: %d\n", LOG_LEVEL);
    if (LOG_LEVEL >= LOG_LEVEL_INFO)
        printf("(All logs enabled: ERROR, WARN, INFO)\n");
    else if (LOG_LEVEL >= LOG_LEVEL_WARN)
        printf("(ERROR and WARN enabled, INFO disabled)\n");
    else
        printf("(Only ERROR enabled)\n");

    printf("\n--- Log Output ---\n");

    // 三种级别的日志调用
    LOG_ERROR("An error occurred: %s", "File not found");
    LOG_WARN("Temperature %d exceeds threshold %d", 85, 75);
    LOG_INFO("Application started successfully.");

    // 无参数的情况（使用 ##__VA_ARGS__ 自动处理）
    LOG_INFO("This is a simple message with no arguments.");

    printf("\n=== End of Log ===\n");
    return 0;
}