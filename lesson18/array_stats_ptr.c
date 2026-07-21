/*
 * array_stats.c
 * 第18课 练习三（选做）：用指针传出多个统计值
 *
 * 功能：对整型数组进行一次遍历，同时计算总和、平均值和最大值，
 *       通过指针参数将结果传回给调用者。
 */

#include <stdio.h>   // printf

/*
 * array_stats:
 *   计算整型数组的总和、平均值和最大值。
 *   arr  : 数组首地址
 *   size : 数组元素个数
 *   sum  : 输出参数，指向存放总和的内存
 *   avg  : 输出参数，指向存放平均值的内存（double）
 *   max  : 输出参数，指向存放最大值的内存
 *
 *   注意：调用者需要为 sum, avg, max 提供实际变量的地址。
 */
void array_stats(int arr[], int size, int *sum, double *avg, int *max)
{
    // 初始化：假设第一个元素既是最大值，也是和的起点
    *max = arr[0];
    int total = 0;   // 使用局部变量累加，避免频繁解引用

    for (int i = 0; i < size; i++)
    {
        total += arr[i];                 // 累加到局部变量
        if (arr[i] > *max) {
            *max = arr[i];              // 更新最大值（写入外部变量）
        }
    }

    // 将最终的总和写入外部变量
    *sum = total;

    // 计算平均值，注意进行浮点除法
    *avg = (double)total / size;
}

int main(void)
{
    printf("=== Array Stats via Pointers ===\n\n");

    // 1. 准备测试数据
    int data[] = {5, 2, 8, 1, 9, 3};
    int n = sizeof(data) / sizeof(data[0]);   // 计算数组长度

    // 2. 定义用于接收结果的变量
    int sum_result;
    double avg_result;
    int max_result;

    // 3. 调用统计函数，传入各变量的地址
    array_stats(data, n, &sum_result, &avg_result, &max_result);

    // 4. 打印结果
    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n\n");
    printf("Sum    : %d\n", sum_result);
    printf("Average: %.2f\n", avg_result);
    printf("Max    : %d\n", max_result);

    return 0;
}