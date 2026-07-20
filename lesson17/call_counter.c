/*
 * call_counter.c
 * 第17课 练习一：函数调用计数器
 *
 * 功能：定义一个 hello() 函数，每次调用时打印问候语并显示调用次数。
 *       使用 static 局部变量实现调用计数，不允许使用全局变量。
 */

#include <stdio.h>

// 函数原型：无参数，无返回值
void hello(void);

int main(void)
{
    printf("=== Call Counter Demo ===\n\n");

    // 循环调用 hello 函数 5 次
    for (int i = 0; i < 5; i++) {
        hello();
    }

    return 0;
}

/*
 * hello:
 *   打印一条问候信息，并显示这是第几次被调用。
 *   使用 static 局部变量记录调用次数，该变量只在首次调用时初始化为 0，
 *   之后每次调用都会保留上次修改后的值。
 */
void hello(void)
{
    // static 局部变量：只初始化一次，生命周期贯穿整个程序
    static int call_count = 0;

    call_count++;   // 每次调用计数器加 1

    printf("Hello! (called %d time(s))\n", call_count);
}