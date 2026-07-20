/*
 * main.c
 * 练习二：extern 跨文件全局变量实验
 *
 * 功能：使用 extern 声明引用在 config.c 中定义的全局变量。
 */

#include <stdio.h>

// extern 声明：告诉编译器 max_users 在另一个文件定义
extern int max_users;

int main(void)
{
    printf("=== Global Share Demo ===\n");
    printf("Max users (from extern): %d\n", max_users);

    return 0;
}