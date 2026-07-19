/*
 * array_stats.c
 * 第16课 练习二：数组统计函数
 *
 * 功能：对给定整型数组计算总和、平均值、最大值。
 *       通过函数封装统计逻辑，主函数只负责调用和输出。
 */

#include <stdio.h>

/* ---------- 函数原型 ---------- */
int sum_array(int arr[], int size);           // 计算总和
double average(int arr[], int size);          // 计算平均值
int max_in_array(int arr[], int size);        // 寻找最大值

/* ---------- 主函数 ---------- */
int main(void)
{
    int scores[] = {10, 20, 30, 40, 50};     // 预定义数组
    int size = sizeof(scores) / sizeof(scores[0]); // 计算数组长度（仅在 main 中有效）

    printf("=== Array Statistics ===\n\n");

    // 打印原始数组
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", scores[i]);
    }
    printf("\n\n");

    // 调用统计函数并打印结果
    int sum = sum_array(scores, size);
    printf("Sum      : %d\n", sum);

    double avg = average(scores, size);
    printf("Average  : %.2f\n", avg);

    int max = max_in_array(scores, size);
    printf("Max      : %d\n", max);

    return 0;
}

/* ---------- 函数定义 ---------- */

/*
 * sum_array:
 *   计算整型数组所有元素的和。
 *   arr : 数组首地址
 *   size: 数组长度
 *   return: 元素总和
 */
int sum_array(int arr[], int size)
{
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];
    }
    return total;
}

/*
 * average:
 *   计算整型数组元素的平均值（浮点数）。
 *   arr : 数组首地址
 *   size: 数组长度
 *   return: 平均值 (double)
 *
 *   注意：必须先转换为 double 再做除法，否则整数除法会丢失小数。
 */
double average(int arr[], int size)
{
    if (size == 0) return 0.0;          // 防止除零错误
    int total = sum_array(arr, size);   // 复用 sum_array，避免重复代码
    return (double)total / size;        // 强制转换为浮点除法
}

/*
 * max_in_array:
 *   返回数组中的最大值。
 *   arr : 数组首地址
 *   size: 数组长度
 *   return: 数组中的最大值
 *
 *   注意：假设 size >= 1，否则行为未定义。
 */
int max_in_array(int arr[], int size)
{
    int max_val = arr[0];   // 初始化为第一个元素
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}