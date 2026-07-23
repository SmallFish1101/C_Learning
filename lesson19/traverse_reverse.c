/*
 * traverse_reverse.c
 * 第19课 练习一：用三种方式遍历数组，并用指针法原地反转
 *
 * 功能：
 *   1. 分别用下标法、指针偏移法、指针自增法打印数组。
 *   2. 用指针法实现数组原地反转。
 *   3. 打印反转后的数组。
 */

#include <stdio.h>

// 函数原型：用指针法原地反转数组
void reverse_array(int *arr, int size);

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);   // 计算数组长度

    printf("=== Traverse & Reverse Array ===\n\n");

    // ----- 1. 用三种方式打印原始数组 -----
    printf("Original array:\n");

    // ① 下标法（你最熟悉的写法）
    printf("  [index method] ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // ② 指针偏移法（底层等价于下标法）
    printf("  [offset method] ");
    for (int i = 0; i < n; i++) {
        printf("%d ", *(arr + i));   // *(arr + i) 就是 arr[i]
    }
    printf("\n");

    // ③ 指针自增法（移动指针本身，效率最高）
    printf("  [pointer inc.]  ");
    for (int *p = arr; p < arr + n; p++) {
        printf("%d ", *p);           // *p 是当前元素
    }
    printf("\n\n");

    // ----- 2. 原地反转数组（指针法）-----
    reverse_array(arr, n);

    // ----- 3. 打印反转后的数组（任选一种方式）-----
    printf("Reversed array:\n");
    printf("  [pointer inc.]  ");
    for (int *p = arr; p < arr + n; p++) {
        printf("%d ", *p);
    }
    printf("\n");

    return 0;
}

/*
 * reverse_array:
 *   原地反转整型数组（不创建新数组）。
 *   arr : 数组首地址
 *   size: 数组元素个数
 *
 *   原理：使用两个指针 left 和 right，
 *         left 指向开头，right 指向末尾，
 *         交换两个指针指向的值，然后向中间靠拢，直到相遇。
 */
void reverse_array(int *arr, int size)
{
    int *left = arr;                  // left 指向第一个元素
    int *right = arr + size - 1;      // right 指向最后一个元素

    while (left < right) {
        // 三步交换 *left 和 *right
        int temp = *left;
        *left = *right;
        *right = temp;

        // 指针移动：left 向后，right 向前
        left++;
        right--;
    }
}