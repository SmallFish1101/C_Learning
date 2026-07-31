/*
 * fix_leak.c
 * 第29课 练习一：修复内存泄漏
 *
 * 功能：先制造内存泄漏，用 Valgrind 检测，
 *       然后修改代码添加 free，再次验证无泄漏。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * create_array:
 *   创建一个动态分配的 int 数组，并填充数据。
 *   参数 n: 数组元素个数
 *   返回: 指向数组的指针（调用者负责释放！）
 */
int *create_array(int n)
{
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Error: malloc failed.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        arr[i] = i * 10;   // 填充：0, 10, 20, 30, ...
    }

    return arr;
}

/*
 * duplicate_string:
 *   复制一个字符串到新分配的内存中。
 *   参数 src: 源字符串
 *   返回: 指向新副本的指针（调用者负责释放！）
 */
char *duplicate_string(const char *src)
{
    size_t len = strlen(src) + 1;
    char *copy = (char *)malloc(len);
    if (copy == NULL) {
        printf("Error: malloc failed.\n");
        exit(1);
    }
    strcpy(copy, src);
    return copy;
}

int main(void)
{
    printf("=== Memory Leak Demo ===\n");

    // 1. 分配数组，打印后忘记释放
    int *data = create_array(5);
    printf("Data array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // 2. 分配字符串副本，打印后忘记释放
    char *name = duplicate_string("Zhang San");
    printf("Name: %s\n", name);

    // ========== 泄漏点 ==========
    // 这里缺少 free(data); 和 free(name);
    // Valgrind 将在第 28 行（int *data = ...）和第 33 行（char *name = ...）
    // 分别报告两次内存泄漏。

     // ========== 修复：添加 free ==========
    free(data);
    free(name);
    printf("Program exiting (with memory leaks)...\n");
    return 0;
}