/*
 * array_copy.c
 * 第19课 练习三（选做）：用指针自增法实现数组复制
 *
 * 功能：用指针运算将源数组的内容复制到目标数组。
 *       全程不使用下标 []，仅用指针自增。
 */

#include <stdio.h>

// 函数原型：复制数组
void array_copy(int *dest, const int *src, int size);

int main(void)
{
    int src[] = {10, 20, 30, 40, 50};   // 源数组
    int dest[5] = {0};                  // 目标数组（初始化为全零）
    int n = sizeof(src) / sizeof(src[0]);

    printf("=== Array Copy using Pointers ===\n\n");

    // 打印源数组
    printf("Source array:      ");
    for (int i = 0; i < n; i++) {
        printf("%d ", src[i]);
    }
    printf("\n");

    // 调用复制函数
    array_copy(dest, src, n);

    // 打印目标数组，验证复制成功
    printf("Destination array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", dest[i]);
    }
    printf("\n");

    // 验证：比较两个数组元素是否完全一致
    int is_equal = 1;
    for (int i = 0; i < n; i++) {
        if (src[i] != dest[i]) {
            is_equal = 0;
            break;
        }
    }
    printf("\nVerification: %s\n", is_equal ? "PASS (arrays match)" : "FAIL (arrays differ)");

    return 0;
}

/*
 * array_copy:
 *   使用指针自增法将源数组复制到目标数组。
 *   dest : 目标数组首地址（可写）
 *   src  : 源数组首地址（只读）
 *   size : 要复制的元素个数
 *
 *   核心：*dest++ = *src++;
 *   这条语句先执行赋值，再让两个指针都后移一个元素。
 */
void array_copy(int *dest, const int *src, int size)
{
    // 循环 size 次，每次复制一个元素，指针自动后移
    while (size-- > 0) {
        *dest++ = *src++;   // 一行完成：取值 → 赋值 → 移动两个指针
    }
    // 循环结束时，dest 和 src 都指向各自数组的末尾
}