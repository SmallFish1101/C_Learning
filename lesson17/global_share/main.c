/*
 * main.c
 * 通过 config.h 提供的函数接口访问配置，不再直接 extern 变量。
 */

#include <stdio.h>
#include "config.h"    // 包含头文件即可使用函数

int main(void)
{
    printf("=== Access via Functions ===\n");

    // 读取初始值
    printf("Initial max_users: %d\n", get_max_users());
    printf("Initial timeout  : %d\n", get_timeout());

    // 修改配置
    set_max_users(500);
    set_timeout(60);

    // 再次读取验证
    printf("\nAfter update:\n");
    printf("max_users: %d\n", get_max_users());
    printf("timeout  : %d\n", get_timeout());

    // 尝试设置非法值（应被忽略）
    set_max_users(99999);
    printf("\nAfter invalid update:\n");
    printf("max_users: %d (should still be 500)\n", get_max_users());

    return 0;
}