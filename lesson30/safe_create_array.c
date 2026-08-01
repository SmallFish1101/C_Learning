/*
 * safe_create_array.c
 * 第30课 练习一：用二级指针实现安全的数组创建函数
 *
 * 功能：通过二级指针参数，在函数内部分配数组并传出。
 *       展示如何"修改外部指针变量"的标准模式。
 */

#include <stdio.h>    // printf
#include <stdlib.h>   // malloc, free, exit
#include <stdbool.h>  // bool, true, false

/*
 * create_array:
 *   在堆上分配 n 个 int 的数组，填充 1~n。
 *   通过二级指针 arr 将结果传出。
 *
 *   参数 arr: 二级指针，指向调用者中 int* 变量的地址
 *   参数 n:   要分配的数组元素个数（必须 > 0）
 *   返回:     true 表示分配成功，false 表示失败
 *
 *   用法:
 *     int *data = NULL;
 *     if (create_array(&data, 10)) {
 *         // 使用 data[0]..data[9]
 *         free(data);
 *     }
 */
bool create_array(int **arr, int n)
{
    // 1. 防御性检查：指针参数和大小必须合法
    if (arr == NULL || n <= 0) {
        return false;
    }

    // 2. 在堆上分配内存
    int *new_arr = (int *)malloc(n * sizeof(int));
    if (new_arr == NULL) {
        // 分配失败：将外部指针置为 NULL，返回 false
        *arr = NULL;
        return false;
    }

    // 3. 填充数据：1, 2, 3, ..., n
    for (int i = 0; i < n; i++) {
        new_arr[i] = i + 1;
    }

    // 4. ★ 关键：通过解引用二级指针，修改外部的 int* 变量本身
    *arr = new_arr;

    return true;   // 成功
}

/*
 * print_array:
 *   打印 int 数组的所有元素。
 *   参数 arr: 数组首地址
 *   参数 n:   元素个数
 */
void print_array(const int *arr, int n)
{
    if (arr == NULL || n <= 0) {
        printf("  (empty or invalid)\n");
        return;
    }
    printf("  [");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

// ========== 主函数：测试 ==========
int main(void)
{
    printf("=== Safe Array Creation via Double Pointer ===\n\n");

    int *data = NULL;   // ★ 初始化为 NULL（第29课铁律）
    int n = 8;

    printf("Attempting to create an array of %d elements...\n", n);

    // 调用 create_array，传递 data 自己的地址（&data）
    if (create_array(&data, n)) {
        printf("Success! Array contents:\n");
        print_array(data, n);
    } else {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    // ★ 使用完毕后释放内存，并将指针置为 NULL
    free(data);
    data = NULL;

    printf("Memory freed. Program exiting.\n");
    return 0;
}