/*
 * string_ptr.c
 * 第18课 练习二：指针与字符串首接触
 *
 * 功能：用指针遍历字符数组，打印每个字符及其 ASCII 码。
 *       对比下标访问和指针偏移的等价性，预习第19课内容。
 */

#include <stdio.h>

// 函数原型：打印字符串中每个字符的详细信息
void print_chars(const char *str);

int main(void)
{
    printf("=== Pointer and String Demo ===\n\n");

    // 定义一个字符数组（字符串），编译器自动在末尾加 '\0'
    char str[] = "Hello";

    // ---- 方法一：调用封装函数，使用指针遍历 ----
    printf("Using pointer traversal:\n");
    print_chars(str);   // 传入数组名，等价于传入首地址

    // ---- 方法二：演示 *(str + i) 和 str[i] 的等价性 ----
    printf("\nUsing pointer offset (*(str + i)):\n");
    for (int i = 0; str[i] != '\0'; i++)
    {
        // str[i] 的底层实现就是 *(str + i)
        printf("  [%d] %c (ASCII %d)\n", i, *(str + i), *(str + i));
    }

    return 0;
}

/*
 * print_chars:
 *   使用指针自增遍历字符串，打印每个字符及其 ASCII 码。
 *   str: 指向字符串首字符的指针（只读，因此加 const）
 */
void print_chars(const char *str)
{
    int index = 0;   // 用于显示位置编号

    // 遍历直到遇到字符串结束符 '\0'
    // 循环中，ptr 每次自增，指向下一个字符
    for (const char *ptr = str; *ptr != '\0'; ptr++)
    {
        // *ptr 就是当前字符
        // %c 打印字符本身，%d 打印它的 ASCII 码
        printf("  [%d] %c (ASCII %d)\n", index, *ptr, *ptr);
        index++;
    }
}